/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <string.h>

#include "matrix.h"

matrix create_matrix(size_t height, size_t width)
{
    return (matrix) {.mat = malloc(height * width), .height = height, .width = width};
}

void destroy_matrix(matrix* mat)
{
    free(mat->mat);
    mat->mat = NULL;
}

matrix zero_matrix(size_t height, size_t width)
{
    return fill_zeroes(create_matrix(height, width));
}

matrix identity_matrix(size_t size)
{
    matrix mat = zero_matrix(size, size);

    for (size_t i = 0; i < size; ++i)
        *(mat.mat + size * i + i) = 1;

    return mat;
}

matrix copy(matrix mat)
{
    matrix new_mat = create_matrix(mat.height, mat.width);
    memcpy(new_mat.mat, mat.mat, mat.height * mat.width);

    return new_mat;
}

matrix fill_zeroes(matrix mat)
{
    for (size_t i = 0; i < mat.height * mat.width; ++i)
        *(mat.mat + i) = 0;
    return mat;
}

double* access(matrix mat, size_t i, size_t j)
{
    if (i > mat.height || j > mat.width)
        return NULL;

    return (mat.mat + i * mat.width + j);
}
