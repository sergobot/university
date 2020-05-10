/** Copyright 2018-2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "12.1/array_io.h"
#include "12.2/array_analysis.h"

#define ARRAY_SIZE 100

int main()
{
    printf("Welcome to 12.2! Please enter desired array size (up to %d):\n", ARRAY_SIZE);
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
        printf("Invalid input");
        return 1;
    }

    printf("The array has %d sign changes\n", sign_changes(a, n));
    printf("Max monotonous subarray length is %d\n", max_monotonous_subarray_length(a, n));
    printf("Array is %ssorted ascending\n", is_sorted(a, n, 1) ? "" : "NOT ");
    printf("Array is %ssorted descending\n", is_sorted(a, n, 0) ? "": "NOT ");
    return 0;
}
