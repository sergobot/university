/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdlib.h>
#include "binary_operations.h"

void* find_in_array(void *a, void *e, int length, int size, compare f)
{
    int l = 0, r = length - 1;

    while (l <= r)
    {
        int m = (l + r) / 2;

        switch(f(e, a + size * m))
        {
        case -1:
            r = m - 1;
            break;
        case 0:
            return a + size * m;
        case 1:
            l = m + 1;
            break;
        default:
            return NULL;
        }
    }

    return NULL;
}

int find_place_to_put(void *a, void *e, int length, int size, compare f)
{
    int l = 0, r = length - 1;

    while (l <= r)
    {
        int m = (l + r) / 2;

        switch(f(e, a + size * m))
        {
        case -1:
            r = m - 1;
            break;
        case 0:
            while (f(e, a + size * m) == 0)
                ++m;
            return m;
        case 1:
            l = m + 1;
            break;
        default:
            return -1;
        }
    }

    if (f(e, a) == -1)
        return 0;
    else if (f(e, a + (length - 1) * size) == 1)
        return length;
    else
        return -1;
}
