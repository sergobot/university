/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#ifndef UNIVERSITY_TASK_3_H
#define UNIVERSITY_TASK_3_H

#include <iostream>
#include <limits>

void allocate_dynamic_matrix(double **(&mat), size_t rows, size_t cols) {
    mat = new double *[rows];
    for (size_t j = 0; j < rows; ++j)
        mat[j] = new double[cols];
}

void destroy_dynamic_matrix(double **(&mat), size_t rows) {
    for (size_t j = 0; j < rows; ++j)
        delete[] mat[j];
    delete[] mat;
    mat = nullptr;
}

size_t remove_rows_larger_than_previous(double **mat, size_t rows, size_t cols) {
    double prev_sum, cur_sum = 0;
    size_t new_rows = cols > 0;

    for (size_t i = 0; i < rows; ++i) {
        prev_sum = cur_sum;
        cur_sum = 0;
        for (size_t j = 0; j < cols; ++j)
            cur_sum += mat[i][j];

        if (i > 0 && cur_sum <= prev_sum) {
            if (i != new_rows)
            {
                double *temp = mat[new_rows];
                mat[new_rows] = mat[i];
                mat[i] = temp;
            }
            ++new_rows;
        }
    }

    return new_rows;
}

template<size_t max_rows, size_t max_cols>
size_t remove_rows_larger_than_previous(double mat[max_rows][max_cols], size_t rows, size_t cols) {
    double prev_sum, cur_sum;
    size_t new_rows = cols > 0;

    for (size_t i = 0; i < std::min(rows, max_rows); ++i) {
        prev_sum = cur_sum;
        cur_sum = 0;
        for (size_t j = 0; j < std::min(cols, max_cols); ++j)
            cur_sum += mat[i][j];

        if (i > 0 && cur_sum <= prev_sum) {
            if (i != new_rows)
                for (size_t j = 0; j < std::min(cols, max_cols); ++j)
                    mat[new_rows][j] = mat[i][j];
            ++new_rows;
        }
    }

    return new_rows;
}

template<size_t max_rows, size_t max_cols>
void print_matrix(double mat[max_rows][max_cols], size_t rows, size_t cols) {
    for (size_t i = 0; i < std::min(rows, max_rows); ++i, std::cout << std::endl)
        for (size_t j = 0; j < std::min(cols, max_cols); ++j)
            std::cout << mat[i][j] << (j < cols - 1 ? "\t" : "");
}

void print_matrix(double **mat, size_t rows, size_t cols) {
    for (size_t i = 0; i < rows; ++i, std::cout << std::endl)
        for (size_t j = 0; j < cols; ++j)
            std::cout << mat[i][j] << (j < cols - 1 ? "\t" : "");
}

#endif //UNIVERSITY_TASK_3_H
