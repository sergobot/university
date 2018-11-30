/** Copyright 2018, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <stdlib.h>

#include "11.3/print_in_base.h"

int main()
{
    printf("Welcome to 11.3! Please enter a number and required base:\n");
    int a, base;
    if (scanf("%d%d", &a, &base) != 2)
    {
        printf("Invalid input: two numbers expected. Exiting.\n");
        return 1;
    }

    if (base > 16 || base < 2)
    {
        printf("Invalid base %d: base should be between 2 and 16 (including)", base);
        return 1;
    }

    print_in_base(a, base);

    return 0;
}
