/** Copyright 2018-2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "12.1/array_io.h"
#include "12.2/array_analysis.h"

#define ARRAY_SIZE 5

int main()
{
    printf("Welcome to 12.2! Please enter %d integers:\n", ARRAY_SIZE);
    int a[ARRAY_SIZE];

    if (!scan_int(a, ARRAY_SIZE))
    {
        printf("Invalid input");
        return 1;
    }

    printf("The array has %d sign changes\n", sign_changes(a, ARRAY_SIZE));
    printf("Max monotonous subarray length is %d\n", max_monotonous_subarray_length(a, ARRAY_SIZE));
    printf("Array is %ssorted ascending\n", is_sorted(a, ARRAY_SIZE, 1) ? "" : "NOT ");
    printf("Array is %ssorted descending\n", is_sorted(a, ARRAY_SIZE, 0) ? "": "NOT ");
    return 0;
}
