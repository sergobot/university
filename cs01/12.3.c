/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "12.1/array_io.h"
#include "12.3/odd_even.h"

#define ARRAY_SIZE 100

int main()
{
    printf("Welcome to 12.3! Please enter desired array size (up to %d):\n", ARRAY_SIZE);
    int a[ARRAY_SIZE], b[ARRAY_SIZE];
    size_t n;

    if (scanf("%lu", (long unsigned*)&n) != 1)
    {
        printf("Invalid input\n");
        return 1;
    }

    printf("Now enter %lu numbers:\n", (long unsigned)n);
    if (!scan_int(a, n))
    {
        printf("Invalid input");
        return 1;
    }

    for (size_t i = 0; i < n; ++i)
        b[i] = a[i];

    printf("Array after removing odd numbers: ");
    print_int(a, remove_odd_even(a, n, 1));
    printf("Array after removing even numbers: ");
    print_int(b, remove_odd_even(b, n, 0));
    return 0;
}
