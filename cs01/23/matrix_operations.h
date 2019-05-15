/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef MATRIX_OPERATIONS_H
#define MATRIX_OPERATIONS_H

#include "matrix.h"

matrix add(matrix a, matrix b, matrix result);
matrix dot(matrix a, matrix b, matrix result);

void mul(matrix mat, double a);
void mul_row(matrix mat, size_t row, double a);
void swap_rows(matrix mat, size_t a, size_t b);
void add_rows(matrix mat, size_t a, size_t b);

matrix transpose(matrix mat);
matrix inverse(matrix mat);

#endif // MATRIX_OPERATIONS_H
