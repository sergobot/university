/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <string>
#include <fstream>
#include <algorithm>
#include <array>
#include <iostream>
#include <functional>

using namespace std;

static const size_t DEFAULT_SPACE_OFFSET = 4;

struct Employee
{
    string last_name;
    string occupation;
    size_t salary = 0;
};

struct Department
{
    size_t id = 0, size = 0;
    Employee *employees = nullptr;
};

/*
 * The file format:
 *  - First line must contain total number of departments described
 *  - Then, for each department, first line must contain its id, and the second its number of employees
 *  - Next, an employee on every row, with its fields separated by spaces.
 *
 * An example:
 * 2                        -- total number of departments
 * 1                        -- one employee in the first department
 * Mark,CEO,100500          -- last name, occupation, salary
 * 2                        -- two employees in the second department
 * Joe,CFO,100501           -- last name, occupation, salary
 * Elon,CTO,420420          -- last name, occupation, salary
 */
size_t create_departments_from_file(const string &filename, Department *&departments)
{
    ifstream fin(filename);
    if(!fin.is_open())
        throw std::runtime_error("Could not open file");

    size_t departments_count;
    fin >> departments_count;

    departments = new Department[departments_count];
    for (size_t i = 0; i < departments_count; ++i)
    {
        fin >> departments[i].id >> departments[i].size;

        departments[i].employees = new Employee[departments[i].size];
        for (size_t j = 0; j < departments[i].size; ++j)
        {
            auto &employee = departments[i].employees[j];
            fin >> employee.last_name >> employee.occupation >> employee.salary;
        }
    }

    return departments_count;
}

void sort_employees(Employee *employees, size_t count, bool ascending = true)
{
    std::sort(employees, employees + count,
              [ascending](const Employee & a, const Employee & b) -> bool
              { return ascending ? a.last_name < b.last_name : a.last_name > b.last_name; }
    );
}

void sort_departments(Department **departments, size_t count, bool ascending = true)
{
    std::sort<Department**>(departments, departments + count,
              [ascending](const Department * a, const Department * b) -> bool
              { return ascending ? a->id < b->id : a->id > b->id; }
    );
}

void sort_departments_and_employees(Department **departments, size_t count, bool ascending = true)
{
    sort_departments(departments, count, ascending);
    for (size_t i = 0; i < count; ++i)
        sort_employees(departments[i]->employees, departments[i]->size, ascending);
}

void print_employee(const Employee &employee, size_t spaces = DEFAULT_SPACE_OFFSET)
{
    cout << string(spaces, ' ') << employee.last_name << " is " << employee.occupation << " with a salary of "
         << employee.salary << endl;
}

void print_department(const Department &department, size_t employee_spaces = DEFAULT_SPACE_OFFSET)
{
    cout << "Department #" << department.id << " of " << department.size << " employees" << endl;
    for (size_t i = 0; i < department.size; ++i)
        print_employee(department.employees[i], employee_spaces);
}

void print_departments(Department** const &departments, size_t count)
{
    cout << "Got " << count << " departments! Here are all of them:" << endl;
    for (size_t i = 0; i < count; ++i)
        print_department(*departments[i]);
}

void destroy_departments(Department *& departments, size_t count)
{
    for (size_t i = 0; i < count; ++i)
        delete[] departments[i].employees;
    delete[] departments;
    departments = nullptr;
}

template<typename T>
T* my_find(T* array, size_t count, function<bool(T&)> condition)
{
    for (size_t i = 0; i < count; ++i)
        if (condition(array[i]))
            return array + i;
    return nullptr;
}

Employee* find_employee_by_last_name_in_departments(Department ** departments, size_t count, string last_name)
{
    Employee *target = nullptr;

    for (size_t i = 0; i < count; ++i)
    {
        target = my_find<Employee>(departments[i]->employees, departments[i]->size,
                                   [last_name](Employee &e) -> bool { return e.last_name == last_name; });
        if (target)
            break;
    }

    return target;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        cout << "This program reads file with departments, sorts them by department id and employee's last name," << endl
             << "then prints the departments in a human-readable format" << endl << endl
             << "Usage:" << endl
             << "  ./task-7 PATH_TO_INPUT_FILE" << endl << endl
             << "This program is distributed under the MIT licence." << endl
             << "Copyright (c) Sergey Popov (me@sergobot.me)" << endl;

        return 1;
    }

    Department *departments;
    size_t count = create_departments_from_file(argv[1], departments);

    auto **pDepartments = new Department*[count];
    for (size_t i = 0; i < count; ++i)
        pDepartments[i] = departments + i;

    sort_departments_and_employees(pDepartments, count);

    print_departments(pDepartments, count);

    string perform_search;
    cout << endl << endl << "Would you like to find someone? [Yy/Nn] ";
    cin >> perform_search;
    if (perform_search == "Y" || perform_search == "y")
    {
        string last_name;
        cout << "Please enter their last name: ";
        cin >> last_name;
        Employee *emp = find_employee_by_last_name_in_departments(pDepartments, count, last_name);
        if (emp)
            cout << "Employee " << emp->last_name << " found! They work as " << emp->occupation << " and earn " << emp->salary << endl;
        else
            cout << "Employee not found!" << endl;
    }
    else if (perform_search == "N" || perform_search == "n")
        cout << "Your choice! Have a nice day anyways :)" << endl;
    else
        cout << "Sorry, didn't understand. Exiting!" << endl;

    destroy_departments(departments, count);
    delete[] pDepartments;

    return 0;
}