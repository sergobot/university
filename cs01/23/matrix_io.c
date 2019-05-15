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
    return create_matrix(height, width);
}
