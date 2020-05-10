/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "12.1/array_io.h"

#define ARRAY_SIZE 100
#include "12.5/find_max_row.h"

int main()
{
    printf("Welcome to 12.5! Please enter your 2D array size (up to %d by each dimension):\n", ARRAY_SIZE);
    double a[ARRAY_SIZE][ARRAY_SIZE];
    size_t n, m;

    if (scanf("%lu%lu", (long unsigned*)&n, (long unsigned*)&m) != 2)
    {
        printf("Invalid input\n");
        return 1;
    }

    printf("Now enter %lu rows of %lu numbers:\n", (long unsigned)n, (long unsigned)m);
    for (size_t i = 0; i < n; ++i)
    {
        if (!scan_double(a[i], m))
        {
            printf("Invalid input");
            return 1;
        }
    }

    printf("Row #%lu has the maximum sum\n", find_max_row(a, n, m));
    return 0;
}
