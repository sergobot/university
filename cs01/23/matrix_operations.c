/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "matrix.h"
#include "matrix_operations.h"

matrix add(matrix a, matrix b, matrix result)
{
    if (a.height != b.height || a.width != b.height ||
        a.height != result.height || a.width != result.width)
        return ERRONEOUS_MATRIX;

    for (size_t i = 0; i < result.height; ++i)
        for (size_t j = 0; j < result.width; ++j)
            *access(result, i, j) = *access(a, i, j) + *access(b, i, j);

    return result;
}

matrix dot(matrix a, matrix b, matrix result)
{
    if (a.width != b.height || a.height != result.height || b.width != result.width)
        return ERRONEOUS_MATRIX;

    for (size_t i = 0; i < result.height; ++i)
        for (size_t j = 0; j < result.width; ++j)
        {
            double sum = 0;
            for (size_t k = 0; k < a.width; ++k)
                sum += (*access(a, i, k)) * (*access(b, k, j));
            *access(result, i, j) = sum;
        }

    return result;
}

void mul(matrix mat, double a)
{
    for (size_t i = 0; i < mat.height * mat.width; ++i)
        *(mat.mat + i) *= a;
}

void mul_row(matrix mat, size_t row, double a)
{
    if (row >= mat.height)
        return;

    for (size_t i = 0; i < mat.width; ++i)
        *access(mat, row, i) *= a;
}

void swap_rows(matrix mat, size_t a, size_t b)
{
    if (a >= mat.height || b >= mat.height)
        return;

    for (size_t i = 0; i < mat.width; ++i)
    {
        double c = *access(mat, a, i);
        *access(mat, a, i) = *access(mat, b, i);
        *access(mat, b, i) = c;
    }
}

void add_rows(matrix mat, size_t a, size_t b)
{
    if (a >= mat.height || b >= mat.height)
        return;

    for (size_t i = 0; i < mat.width; ++i)
        *access(mat, a, i) += *access(mat, b, i);
}

matrix transpose(matrix mat)
{
    matrix transposed = create_matrix(mat.width, mat.height);
    for (size_t i = 0; i < mat.height; ++i)
        for (size_t j = 0; j < mat.width; ++j)
            *access(transposed, j, i) = *access(mat, i, j);

    return transposed;
}

matrix inverse(matrix mat)
{
    if (mat.height != mat.width)
        return ERRONEOUS_MATRIX;

    matrix temp = copy(mat);
    matrix inv = identity_matrix(mat.height);

    for (size_t i = 0; i < temp.width; ++i)
        for (size_t j = 0; j < temp.height; ++j)
            if (i != j) {
                // TODO: It may be possible to swap rows to eliminate diagonal zeroes
                if (*access(temp, i, i) == 0)
                    return ERRONEOUS_MATRIX;

                double factor = *access(temp, j, i) / *access(temp, i, i);
                for (size_t k = 0; k < temp.width; ++k) {
                    *access(temp, j, k) -= *access(temp, i, k) * factor;
                    *access(inv, j, k) -= *access(inv, i, k) * factor;
                }
            }

    for (size_t i = 0; i < temp.height; i++) {
        double factor = *access(temp, i, i);
        for (size_t j = 0; j < temp.width; j++)
            *access(inv, i, j) = *access(inv, i, j) / factor;
    }

    destroy_matrix(&temp);

    return inv;
}
