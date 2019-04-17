/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "find_smallest.h"

const long* find_smallest(const long* start, size_t length)
{
    const long* smallest = start;
    const long* end = start + length * sizeof(long);

    while(start != end)
    {
        if (*start > 0 && *start < *smallest)
            smallest = start;

        start += sizeof(long);
    }

    return smallest;
}
