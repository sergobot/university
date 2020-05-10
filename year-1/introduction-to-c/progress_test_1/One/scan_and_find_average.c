/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#include <stdio.h>
#include "scan_and_find_average.h"

int scan_double(double *d)
{
    if (scanf("%lf", d) != 1)
    {
        printf("Invalid input: expected a real number. Exiting.\n");
        return 0;
    }
    return 1;
}

int scan_and_find_average(double stop_num)
{
    double sum = 0;
    int count  = 0;
    double d = 0;
    if (!scan_double(&d))
        return 1;

    while (d != stop_num)
    {
        sum += d;
        ++count;

        scan_double(&d);
    }

    return (int)(sum / count);
}
