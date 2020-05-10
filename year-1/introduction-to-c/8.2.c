/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>

int is_natural_power_of(int, int);

int main()
{
    int n, m;
    printf("Welcome to 8.2! Please enter two numbers (n and m):\n");
    if (scanf("%d%d", &n, &m) != 2)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    printf(is_natural_power_of(n, m) ?
           "%d is a natural power of %d" :
           "%d is not a natural power of %d",
           n, m);
}

int is_natural_power_of(int n, int m)
{
    int p = m;
    while (p < n)
        p *= m;

    return p == n;
}
