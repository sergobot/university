/** Copyright 2018-2019, Sergey Popov (me@sergobot.me) **/

#include <stdlib.h>
#include "array_analysis.h"

int sign_changes(int *arr, int n)
{
    int previous_sign = arr[0] / abs(arr[0]);
    int changes = 0;

    for (int i = 1; i < n; ++i)
    {
        int new_sign = arr[i] / abs(arr[i]);
        if (new_sign != previous_sign)
        {
            previous_sign = new_sign;
            ++changes;
        }
    }

    return changes;
}

int max_monotonous_subarray_length(int *arr, int n)
{
    int max_length = 1;
    int current_length = 1;
    int ascending = 1;

    for (int i = 1; i < n; ++i)
        if ((arr[i] > arr[i-1]) == ascending)
            ++current_length;
        else
        {
            if (current_length > max_length)
                max_length = current_length;
            current_length = 1;
            ascending = !ascending;
        }

    if (current_length > max_length)
        max_length = current_length;

    return max_length;
}

int is_sorted(int *arr, int n, int ascending)
{
    for (int i = 1; i < n; ++i)
    {
        if (arr[i] != arr[i-1] && (arr[i] > arr[i-1]) != ascending)
            return 0;
    }
    return 1;
}
