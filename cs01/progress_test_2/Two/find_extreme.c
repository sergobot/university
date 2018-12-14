/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#include "find_extreme.h"

/* Find the most differing elements of an array */
double find_extreme(double *a, int length)
{
    // An extreme value is either maximum or minimum, so
    // find them while summing up the array to avoid running
    // through the whole array again.
    double min = a[0], max = a[0], sum = a[0];

    for (int i = 1; i < length; ++i)
    {
        if (a[i] > max) max = a[i];
        else if (a[i] < min) min = a[i];

        sum += a[i];
    }

    double avg = sum / length;
    if (avg - min > max - avg) return min;
    return max;
}
