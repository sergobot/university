/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "12.1/array_io.h"
#include "12.5/find_max_row.h"

#define ARRAY_SIZE 3

int main()
{
    printf("Welcome to 12.5! Please enter %d arrays of %d integers:\n", ARRAY_SIZE, ARRAY_SIZE);
    int a[ARRAY_SIZE][ARRAY_SIZE];

    for (int i = 0; i < ARRAY_SIZE; ++i)
    {
        if (!scan_int(a[i], ARRAY_SIZE))
        {
            printf("Invalid input");
            return 1;
        }
    }

    printf("Row #%d has the maximum sum\n", find_max_row(ARRAY_SIZE, ARRAY_SIZE, a));
    return 0;
}
