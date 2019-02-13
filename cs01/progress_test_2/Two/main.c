/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#include <stdio.h>
#include <stdlib.h>

#include "find_extreme.h"

#define ARRAY_SIZE 100

/* Scans an array of double. In case of failure returns 0, otherwise 1. */
int scanf_double_array(double *a, int n)
{
    if (n < 1)
        return 0;
    for (int i = 0; i < n; ++i)
    {
        if (scanf("%lf", &a[i]) != 1)
        {
            printf("Invalid input: expected a real number! Exiting.\n");
            return 0;
        }
    }
    return 0;
}

int main()
{
    printf("Welcome to Two by Sergobot (All rights reserved)! Please enter length of your array (up to 100):\n");

    int n;
    if (scanf("%d", &n) != 1 || n < 1 || n > 99)
    {
        printf("Invalid input: expected one integer between 1 and 100 (including). Exiting.\n");
        return 1;
    }

    printf("Great! Now enter your array of %d real numbers:\n", n);

    double a[ARRAY_SIZE] = {0};
    if (scanf_double_array(a, n))
        return 1;

    printf("The most extreme element is %lf!\n", find_extreme(a, n));

    return 0;
}
