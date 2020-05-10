/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <math.h>
#include "matrix_operations.h"

matrix add(matrix a, matrix b)
{
    if (a.height != b.height || a.width != b.height)
        return ERRONEOUS_MATRIX;

    matrix result = create_matrix(a.height, a.width);

    for (size_t i = 0; i < result.height; ++i)
        for (size_t j = 0; j < result.width; ++j)
            *access(result, i, j) = *access(a, i, j) + *access(b, i, j);

    return result;
}

matrix dot(matrix a, matrix b)
{
    if (a.width != b.height)
        return ERRONEOUS_MATRIX;

    matrix result = zero_matrix(a.height, b.width);

    for (size_t j = 0; j < result.height; ++j)
        for (size_t i = 0; i < result.width; ++i)
            for (size_t k = 0; k < a.width; ++k)
                *access(result, i, j) += (*access(a, i, k)) * (*access(b, k, j));
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
                // TODO: It may be possible to swap rows to eliminate diagonal zeros
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

matrix exponent(matrix mat)
{
    if (mat.width != mat.height)
        return ERRONEOUS_MATRIX;

    double q = 1;
    matrix result = identity_matrix(mat.height);
    matrix power = identity_matrix(mat.height);

    for (int i = 1; i < 20; ++i)
    {
        matrix temp = dot(power, mat);
        matrix temp2 = copy(temp);
        q /= i;
        mul(temp2, q);
        matrix temp3 = add(result, temp2);

        destroy_matrix(&power);
        power.mat = temp.mat;

        destroy_matrix(&result);
        result.mat = temp3.mat;

        destroy_matrix(&temp2);
    }

    destroy_matrix(&power);
    return result;
}

double frobenious_norm(matrix mat)
{
    double total = 0;
    for (size_t i = 0; i < mat.height * mat.width; ++i)
        total += (*(mat.mat + i)) * (*(mat.mat + i));

    return sqrt(total);
}
