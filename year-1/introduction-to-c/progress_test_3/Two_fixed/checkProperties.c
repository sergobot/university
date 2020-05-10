/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "checkProperties.h"
#include <stdio.h>

double* find_last_element_satisfying_property(double *arr, size_t length, check_property check)
{
    double *end = arr + length * sizeof(double);

    double *last = NULL;
    while (arr < end)
    {
        if (check(*arr))
            last = arr;
        arr += sizeof(double);
    }

    return last;
}
