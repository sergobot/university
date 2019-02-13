/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "12.1/array_io.h"
#include "12.3/odd_even.h"

#define ARRAY_SIZE 5

int main()
{
    printf("Welcome to 12.3! Please enter %d integers:\n", ARRAY_SIZE);
    int a[ARRAY_SIZE], b[ARRAY_SIZE];

    if (!scan_int(a, ARRAY_SIZE))
    {
        printf("Invalid input");
        return 1;
    }

    for (int i = 0; i < ARRAY_SIZE; ++i)
        b[i] = a[i];

    printf("Array after removing odd numbers: ");
    print_int(a, remove_odd_even(a, ARRAY_SIZE, 1));
    printf("Array after removing even numbers: ");
    print_int(b, remove_odd_even(b, ARRAY_SIZE, 0));
    return 0;
}
