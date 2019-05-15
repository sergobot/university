/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "23/matrix.h"
#include "23/matrix_io.h"
#include <stdio.h>

int main()
{
    matrix mat = create_matrix(5, 5);
    print_matrix(mat);

    for (size_t i = 0; i < mat.height * mat.width; ++i)
        *(mat.mat + i * sizeof(double)) = 0;

    for (size_t i = 0; i < 5; ++i)
        *(mat.mat + 5 * i * sizeof(double) + i * sizeof(double)) = 1;

    printf("\n");
    print_matrix(mat);

    destroy_matrix(&mat);

    return 0;
}
