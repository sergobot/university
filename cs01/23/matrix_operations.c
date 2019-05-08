/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "matrix.h"
#include "matrix_operations.h"

matrix mul(matrix mat, double a)
{
    for (size_t i = 0; i < mat.height * mat.width; ++i)
        *(mat.mat + i) *= a;

    return mat;
}

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

matrix mul_row(matrix mat, size_t row, double a)
{
    if (row >= mat.height)
        return ERRONEOUS_MATRIX;

    for (size_t i = 0; i < mat.width; ++i)
        *access(mat, row, i) *= a;

    return mat;
}

matrix swap_rows(matrix mat, size_t a, size_t b)
{
    if (a >= mat.height || b >= mat.height)
        return ERRONEOUS_MATRIX;

    for (size_t i = 0; i < mat.width; ++i)
    {
        double c = *access(mat, a, i);
        *access(mat, a, i) = *access(mat, b, i);
        *access(mat, b, i) = c;
    }

    return mat;
}

matrix add_rows(matrix mat, size_t a, size_t b)
{
    if (a >= mat.height || b >= mat.height)
        return ERRONEOUS_MATRIX;

    for (size_t i = 0; i < mat.width; ++i)
        *access(mat, a, i) += *access(mat, b, i);

    return mat;
}
