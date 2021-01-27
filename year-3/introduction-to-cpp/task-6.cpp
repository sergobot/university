/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>
#include <algorithm>
#include <string>
#include <cctype>
#include <fstream>
#include <filesystem>

// 41s
size_t replace_characters_and_count(std::string &s, char with)
{
    size_t count = 0;
    for (char &c : s)
        if (isalpha(c))
        {
            c = with;
            ++count;
        }

    return count;
}
// 43s
size_t replace_characters_and_count_std(std::string &s, char with)
{
    size_t count = 0;
    std::replace_if(s.begin(), s.end(), [&count](char c){ ++count; return isalpha(c); }, with);
    return count;
}

void replace_characters_from_stream(std::istream &in, std::ostream &out, char with)
{
    std::string s;
    while (std::getline(in, s))
    {
        replace_characters_and_count_std(s, with);
        out << s << std::endl;
    }
}

int main(int argc, char* argv[])
{
    if (argc == 1)
    {
        std::cout
            << "This program replaces all occurrences of alphabetic charactes in files with a '*'.\n\n"
            << "Usage:\n"
            << "  ./task-6 INPUT_FILE [OUTPUT_FILE]\n\n"
            << "INPUT_FILE is mandatory, OUTPUT_FILE is not. If you don't provide the latter one,\n"
            << "the program will ask you to type it.\n\n"
            << "This program is distributed under the MIT licence.\n"
            << "Copyright (c) Sergey Popov (me@sergobot.me)";
    }
    else {
        std::ifstream in(argv[1]);
        std::ofstream out;

        std::string output_name;
        if (argc == 2) {
            while (output_name.empty())
            {
                std::cout << "Please specify the output file: ";
                std::cin >> output_name;
            }
        } else if (argc == 3) {
            output_name = argv[2];
        }

        // Ask whether to overwrite
        std::string answer;
        while (std::filesystem::exists(output_name) && !(answer == "Y" || answer == "y" || answer == "N" || answer == "n"))
        {
            std::cout << "File " << output_name << " already exists. Overwrite? [Y/n] ";
            std::cin >> answer;
        }

        if (answer == "N" || answer == "n")
        {
            std::cout << "Understandable. Have a nice day." << std::endl;
            return 0;
        }

        out.open(output_name);
        replace_characters_from_stream(in, out, '*');

        in.close();
        out.close();
    }

    return 0;
}