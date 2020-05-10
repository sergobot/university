/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <stdlib.h>

#include "longest_vector.h"

int main()
{
    const char *filename = "input.txt";
    FILE *file = fopen(filename, "r");

    if (file == NULL)
    {
        printf("File %s does not exist! Exiting.\n", filename);
        return 1;
    }

    printf("Max. length is %lf", find_longest_vector_in_file(file));

    return 0;
}
