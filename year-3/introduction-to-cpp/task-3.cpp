/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>
#include <vector>
#include "task-3.h"

static const size_t MAX_ROWS = 100;
static const size_t MAX_COLS = 100;

int main() {
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    std::cout.precision(2);

    const size_t rows = 5;
    const size_t cols = 5;

    double static_matrix[MAX_ROWS][MAX_COLS] = {
            {3.52, 4.1, 5.0,  0.1, 3.3},
            {7.6,  4.4, 1.8,  2.3, 6.123},
            {0.9,  3.,  12.3, 1.2, 4.9},
            {6.6,  1.7, 2.8,  0.3, 0.4},
            {1.0,  2.0, 3.0,  4.0, 5.0}
    };

    double **dynamic_matrix;
    allocate_dynamic_matrix(dynamic_matrix, rows, cols);
    for (size_t i = 0; i < rows; ++i)
        for (size_t j = 0; j < cols; ++j)
            dynamic_matrix[i][j] = static_matrix[i][j];


    std::cout << "STATIC -- BEFORE" << std::endl;
    print_matrix<MAX_ROWS, MAX_COLS>(static_matrix, rows, cols);
    size_t new_rows = remove_rows_larger_than_previous<MAX_ROWS, MAX_COLS>(static_matrix, rows, cols);
    std::cout << "STATIC -- AFTER" << std::endl;
    print_matrix<MAX_ROWS, MAX_COLS>(static_matrix, new_rows, cols);

    std::cout << std::endl << "DYNAMIC -- BEFORE" << std::endl;
    print_matrix(dynamic_matrix, rows, cols);
    new_rows = remove_rows_larger_than_previous(dynamic_matrix, rows, cols);
    std::cout << "DYNAMIC -- AFTER" << std::endl;
    print_matrix(dynamic_matrix, new_rows, cols);

    destroy_dynamic_matrix(dynamic_matrix, rows);

    return 0;
}