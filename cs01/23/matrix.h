/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

#define ERRONEOUS_MATRIX (matrix){NULL, 0, 0};
typedef struct {
    double* mat;
    const size_t height;
    const size_t width;
} matrix;

matrix create_matrix(size_t height, size_t width);
void destroy_matrix(matrix *mat);

matrix zero_matrix(size_t height, size_t width);
matrix identity_matrix(size_t size);
matrix copy(matrix mat);

matrix fill_zeroes(matrix mat);
double* access(matrix mat, size_t i, size_t j);

#endif // MATRIX_H
