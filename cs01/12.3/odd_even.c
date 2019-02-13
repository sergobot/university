/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdlib.h>
#include "odd_even.h"

int remove_odd_even(int *arr, size_t n, int oddity)
{
    size_t j = 0;
    for (size_t i = 0; i < n; ++i)
    {
        if (arr[i] % 2 != oddity)
        {
            arr[j] = arr[i];
            ++j;
        }
    }
    return j;
}
