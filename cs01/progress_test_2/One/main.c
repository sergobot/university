/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#include <stdio.h>
#include <stdlib.h>

#include "chebyshev.h"

int main()
{
    printf("Welcome to One by Sergobot (All rights reserved)! Please enter x and n to compute Chebyshev's polynomial:\n");
    double x;
    int n;
    if (scanf("%lf%d", &x, &n) != 2)
    {
        printf("Invalid input: one float and one integer expected! Exiting.");
        return 1;
    }

    printf("Chebuyshev polynomial computed:\n"
           "  * Recursively: U(x, n) = %lf\n"
           "  * Iteratively: U(x, n) = %lf\n",
           chebishev_recursive(x, n), chebishev_iterative(x, n));

    return 0;
}
