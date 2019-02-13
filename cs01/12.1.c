/** Copyright 2018-2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "12.1/array_io.h"

#define ARRAY_SIZE 100

int main()
{
    printf("Welcome to 12.1! Please enter desired array size (up to %d):\n", ARRAY_SIZE);
    int a[ARRAY_SIZE];
    size_t n;

    if (scanf("%lu", (long unsigned*)&n) != 1)
    {
        printf("Invalid input\n");
        return 1;
    }

    printf("Now enter %lu numbers:\n", (long unsigned)n);
    if (!scan_int(a, n))
    {
        printf("Invalid input\n");
        return 1;
    }

    printf("You've entered the following array:\n");
    print_int(a, n);

    return 0;
}
