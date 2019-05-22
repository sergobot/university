/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "23/matrix.h"
#include "23/matrix_io.h"
#include "23/matrix_operations.h"

#include <stdio.h>

int main()
{
    printf("Welcome to 23! Please enter your matrix size (first is height, second is width):\n");
    size_t a, b;
    if (scanf("%ld %ld", (long*)&a, (long*)&b) != 2)
    {
        printf("Invalid input!");
        return 1;
    }
    matrix mat = read_matrix(a, b);
    matrix inv = inverse(mat);
    matrix trans = transpose(mat);

    printf("\nInverse:\n");
    if (inv.mat == NULL)
        printf("Your matrix can't be inverted!\n");
    else
        print_matrix(inv);

    printf("\nTransposed:\n");
    if (trans.mat == NULL)
        printf("Error while transforming matrix!\n");
    else
        print_matrix(trans);

    destroy_matrix(&mat);
    destroy_matrix(&inv);
    destroy_matrix(&trans);

    return 0;
}
