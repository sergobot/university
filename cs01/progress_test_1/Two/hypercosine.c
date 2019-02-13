/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#include <stdlib.h>
#include "hypercosine.h"

double hypercosine(double x, double epsilon, int *count)
{
    /* Start at next_element = 1, as it the first element (n = 0) */
    double next_element = 1;
    int n = 1;
    double sum = next_element;

    while (next_element > epsilon)
    {
        next_element *= x * x / (2 * n * (2 * n - 1));
        sum += next_element;
        ++n;
    }

    if (count != NULL)
        *count = n + 1;

    return sum;
}
