/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#include <stdio.h>
#include <stdlib.h>

#include "scan_and_find_average.h"

int main()
{
    printf("Welcome to One by Sergobot! Please enter the stop-number:\n");
    double d;
    if (scanf("%lf", &d) != 1)
    {
        printf("Invalid input: expected one real number. Exiting.\n");
        return 1;
    }

    printf("Average is %d\n", scan_and_find_average(d));


    return 0;
}
