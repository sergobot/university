/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef FIND_SMALLEST_H
#define FIND_SMALLEST_H

#include <stdlib.h>

/**
 * Returns pointer to the smallest number in an array.
 * @param start - pointer to the array.
 * @param length - length of given array.
 * @return pointer to the smallest number in the array.
 */
const long* find_smallest(const long* start, size_t length);

#endif // FIND_SMALLEST_H
