/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <math.h>
#include "13/integrate.h"

#define NUMBER_OF_FUNCTIONS 6

double f1(double x) { return x * x; }

double f2(double x) { return 2 * x * x + 13 * x - 17; }

double f3(double x) { return 1 / x; }

double f4(double x) { return sqrt(x); }

double f5(double x) { return sin(x); }

double f6(double x) { return atan(x); }

int main()
{
    printf("Welcome to 13! I will compute a few integrals just for you.\n"
           "But first, please tell me required precision:\n");

    double precision;
    if (scanf("%lf", &precision) != 1) {
        printf("Something wrong with your input! Exiting...\n");
        return 1;
    }
    printf("Thanks! Here you go:\n\n");

    mathematical_function functions[NUMBER_OF_FUNCTIONS] = {f1, f2, f3, f4, f5, f6};
    char *formulas[NUMBER_OF_FUNCTIONS] = {
            "y = x^2",
            "y = 2x^2 + 13x - 17",
            "y = 1 / x",
            "y = sqrt(x)",
            "y = sin(x)",
            "y = atan(x)"
    };
    int ranges[NUMBER_OF_FUNCTIONS][2] = {
            {-10, 10},
            {-10, 10},
            {1,   10},
            {0,   10},
            {-10, 10},
            {-10, 10}
    };

    for (int i = 0; i < NUMBER_OF_FUNCTIONS; ++i) {
        printf("%s in range [%d; %d]: %.3lf\n", formulas[i], ranges[i][0], ranges[i][1],
               integrate_iteratively_trapezoid(functions[i], ranges[i][0], ranges[i][1], precision));
    }

    return 0;
}
