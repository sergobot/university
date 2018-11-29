/** Copyright 2018, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <stdlib.h>

void print_in_base(int a, int base);

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
