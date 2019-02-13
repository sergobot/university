/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "odd_even.h"

int remove_odd_even(int *arr, int n, int oddity)
{
    int j = 0;
    for (int i = 0; i < n; ++i)
    {
        if (arr[i] % 2 != oddity)
        {
            arr[j] = arr[i];
            ++j;
        }
    }
    return j;
}
