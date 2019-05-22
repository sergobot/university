/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "23/matrix.h"
#include "23/matrix_io.h"
#include "23/matrix_operations.h"

int main()
{

    matrix mat = read_matrix(3, 3);
    matrix inv = inverse(mat);
    print_matrix(inv);
    destroy_matrix(&mat);
    destroy_matrix(&inv);

    return 0;
}
