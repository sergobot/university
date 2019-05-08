/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.h"

matrix mul(matrix mat, double a);
matrix add(matrix a, matrix b, matrix result);
matrix dot(matrix a, matrix b, matrix result);

matrix mul_row(matrix mat, size_t row, double a);
matrix swap_rows(matrix mat, size_t a, size_t b);
matrix sum_rows(matrix mat, size_t a, size_t b);

matrix transpose(matrix mat);
matrix inverse(matrix mat);

#endif // MATRIX_OPERATIONS_H
