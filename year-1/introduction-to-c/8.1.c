/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>

int digit_sum_in_custom_base(int, int);
int digital_root(int, int);

int main()
{
    int a, base;
    printf("Welcome to 8.1! Please enter a number and the base (n and p):\n");
    if (scanf("%d%d", &a, &base) != 2)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    printf("Digital root of %d in base %d is %d\n", a, base, digital_root(a, base));

    return 0;
}

int digit_sum_in_custom_base(int a, int base)
{
    int s = 0;
    while (a > 0)
    {
        s += a % base;
        a /= base;
    }
    return s;
}

int digital_root(int a, int base)
{
    while (a >= base)
        a = digit_sum_in_custom_base(a, base);

    return a;
}
