/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef CHECKPROPERTIES_H_INCLUDED
#define CHECKPROPERTIES_H_INCLUDED

#include <stdlib.h>

typedef int (*check_property) (double);

/**
 * Find the last element that makes check(element) return non-zero.
 * @param arr - array to iterate over
 * @param length - length of the above array
 * @param check - function that return either 0, or something else
 * @return pointer to the last element that made check function return non-zero;
 */
double* find_last_element_satisfying_property(double *arr, size_t length, check_property check);

#endif // CHECKPROPERTIES_H_INCLUDED
