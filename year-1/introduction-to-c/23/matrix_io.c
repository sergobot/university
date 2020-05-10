/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "matrix_io.h"

void print_matrix(matrix mat)
{
    for (size_t i = 0; i < mat.height; ++i)
    {
        for (size_t j = 0; j < mat.width; ++j)
            printf("%.3lf\t ", *access(mat, i, j));
        printf("\n");
    }
}

matrix read_matrix(size_t height, size_t width)
{
    matrix mat = create_matrix(height, width);

    printf("Please enter your (%ld x %ld) matrix in rows:\n", (long) height, (long) width);

    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < width; ++j) {
            if (scanf("%lf", access(mat, i, j)) != 1) {
                destroy_matrix(&mat);
                return ERRONEOUS_MATRIX;
            }
        }
    }
    return mat;
}
