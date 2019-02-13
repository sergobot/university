/** Copyright 2018-2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "array_io.h"

/** Scans an array of n elemnents of int from stdin **/
int scan_int(int *arr, int n)
{
    for (int i = 0; i < n; ++i)
        if (scanf("%d", &arr[i]) != 1)
            return 0;

    return 1;
}

/** Scans an array of n elemnents of double from stdin **/
int scan_double(double *arr, int n)
{
    for (int i = 0; i < n; ++i)
        if (scanf("%lf", &arr[i]) != 1)
            return 0;

    return 1;
}

/** Prints an array of n elements of type int **/
void print_int(int *arr, int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

/** Prints an array of n elements of type double **/
void print_double(double *arr, int n)
{
    for (int i = 0; i < n; ++i)
        printf("%lf ", arr[i]);
    printf("\n");
}
