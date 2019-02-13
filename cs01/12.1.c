/** Copyright 2018-2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "12.1/array_io.h"

#define ARRAY_SIZE 5

int main()
{
    printf("Welcome to 12.1! Please enter %d integers:\n", ARRAY_SIZE);
    int a[ARRAY_SIZE];

    if (!scan_int(a, ARRAY_SIZE))
    {
        printf("Invalid input");
        return 1;
    }

    printf("You've entered the following array:\n");
    print_int(a, ARRAY_SIZE);

    return 0;
}
