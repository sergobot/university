/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <float.h>
#include "find_max_row.h"

size_t find_max_row(double (*arr)[ARRAY_SIZE], size_t n, size_t m)
{
    double max_sum = -DBL_MAX;
    size_t max_row = 0;
    for (size_t i = 0; i < n; ++i)
    {
        double current_sum = 0;
        for (size_t j = 0; j < m; ++j)
            current_sum += arr[i][j];

        if (max_sum < current_sum)
        {
            max_sum = current_sum;
            max_row = i + 1;
        }
    }

    return max_row;
}
