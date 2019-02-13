/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "find_max_row.h"

int find_max_row(int n, int m, int *arr[m])
{
    int max_sum = 0, max_row = 0;
    for (int i = 0; i < n; ++i)
    {
        int current_sum = 0;
        for (int j = 0; j < m; ++j)
            current_sum += arr[i][j];

        if (max_sum < current_sum)
        {
            max_sum = current_sum;
            max_row = i + 1;
        }
    }

    return max_row;
}
