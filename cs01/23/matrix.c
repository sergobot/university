/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <string.h>
#include "matrix.h"

const matrix ERRONEOUS_MATRIX = (matrix) {NULL, 0, 0};

matrix create_matrix(size_t height, size_t width)
{
    return (matrix) {.mat = malloc(height * width * sizeof(double)), .height = height, .width = width};
}

void destroy_matrix(matrix* mat)
{
    free(mat->mat);
    mat->mat = NULL;
}

matrix zero_matrix(size_t height, size_t width)
{
    matrix mat = create_matrix(height, width);
    fill_zeroes(mat);
    return mat;
}

matrix identity_matrix(size_t size)
{
    matrix mat = zero_matrix(size, size);

    for (size_t i = 0; i < size; ++i)
        *(mat.mat + size * i * sizeof(double) + i * sizeof(double)) = 1;

    return mat;
}

matrix copy(matrix mat)
{
    matrix new_mat = create_matrix(mat.height, mat.width);
    for (size_t i = 0; i < mat.height * mat.width; ++i)
        *(new_mat.mat + i * sizeof(double)) = *(mat.mat + i * sizeof(double));
    return new_mat;
}

void fill_zeroes(matrix mat)
{
    for (size_t i = 0; i < mat.height * mat.width; ++i)
        *(mat.mat + i * sizeof(double)) = 0;
}

double* access(matrix mat, size_t i, size_t j)
{
    if (i > mat.height || j > mat.width)
        return NULL;

    return (mat.mat + i * mat.width * sizeof(double) + j * sizeof(double));
}
