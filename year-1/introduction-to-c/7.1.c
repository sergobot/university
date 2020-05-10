/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>

int main()
{
    int a, n, s = 0;
    printf("Welcome to 7.1.a! Please enter the base:\n");
    if (scanf("%d", &n) != 1)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    printf("Now enter your number:\n");
    if (scanf("%d", &a) != 1)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    while (a > 0)
    {
        s += a % n;
        a /= n;
    }

    printf("The sum is %d\n", s);

    return 0;
}
