/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <stdlib.h>

#include "checkProperties.h"

int check(double a)
{
    return a > 0;
}

int main()
{
    printf("Welcome to Two! Please enter number of elements in your array:\n");

    size_t length;
    if (scanf("%ld", (long*)&length) != 1)
    {
        printf("Invalid input :(\nExiting!\n");
        return 1;
    }

    double *a = malloc(length * sizeof(double));
    double *end = a + length * sizeof(double);

    double *iterator = a;

    printf("Now, enter your array:\n");
    while(iterator < end)
    {
        if (scanf("%lf", iterator) != 1)
        {
            printf("Invalid input :(\nExiting!\n");
            return 1;
        }
        iterator += sizeof(double);
    }

    printf("The last element > 0 is %.3lf\n", *find_last_element_satisfying_property(a, length, check));

    return 0;
}
