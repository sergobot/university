/** Copyright 2018, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "print_in_base.h"

void print_in_base(int a, int base)
{
    if (base > 16 || base < 2)
        return;

    if (a == 0)
    {
        printf("\n");
        return;
    }

    int t = abs(a % base);

    if (t < 10)
        printf("%d", t);
    else
        switch (t)
        {
        case 10:
            printf("A");
            break;
        case 11:
            printf("B");
            break;
        case 12:
            printf("C");
            break;
        case 13:
            printf("D");
            break;
        case 14:
            printf("E");
            break;
        case 15:
            printf("F");
            break;
        default:
            printf("\nInternal error. Please contact the developer.\n");
            break;
        }
    print_in_base(a / base, base);
}
