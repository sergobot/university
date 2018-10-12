/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>

void print_frame(int m, int n, int d)
{
    for (int i = 0; i < d; ++i)
    {
        for (int j = 0; j < m; ++j)
            printf("*");

        printf("\n");
    }

    for (int i = 0; i < n - 2 * d; ++i)
    {
        for (int j = 0; j < d; ++j)
            printf("*");

        for (int j = 0; j < m - 2 * d; ++j)
            printf(" ");

        for (int j = 0; j < d; ++j)
            printf("*");

        printf("\n");
    }

    for (int i = 0; i < d; ++i)
    {
        for (int j = 0; j < m; ++j)
            printf("*");

        printf("\n");
    }
}

int main()
{
    int n, m, d;
    printf("Welcome to 8.3! Please enter three numbers (n, m and d):\n");
    if (scanf("%d%d%d", &n, &m, &d) != 3)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    print_frame(n, m, d);

    return 0;
}
