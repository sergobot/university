/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "find_smallest.h"

const long* find_smallest(const long* start, size_t length)
{
    const long* smallest = NULL;
    const long* end = start + length;

    while(start < end)
    {
        if (*start > 0 && (smallest == NULL || *start < *smallest))
            smallest = start;

        ++start;
    }

    return smallest;
}
