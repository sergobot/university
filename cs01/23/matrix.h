/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef MATRIX_H
#define MATRIX_H

#include <stdlib.h>

typedef double* matrix;

matrix create_matrix(size_t height, size_t width);
matrix zero(matrix);
#endif // MATRIX_H