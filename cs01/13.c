/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <math.h>
#include "13/integrate.h"

#define NUMBER_OF_FUNCTIONS 6

double f1(double x, double *p) { return p[0] * x * x + p[1] * x + p[2]; }

double f2(double x, double *p) { return p[0] * x * x * x + p[1] * x * x + p[2] * x + p[3]; }

double f3(double x, double *p) { return p[0] / x + p[1]; }

double f4(double x, double *p) { return p[1] * sqrt(p[0] * x) + p[2]; }

double f5(double x, double *p) { return p[1] * sin(p[0] * x) + p[2]; }

double f6(double x, double *p) { return p[1] * atan(p[0] * x) + p[2]; }

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
            "y = x^3 + 3x^2 + 3x + 1",
            "y = 1 / x + 3",
            "y = sqrt(x)",
            "y = sin(x)",
            "y = atan(-x) + pi / 2"
    };
    double parameters[NUMBER_OF_FUNCTIONS][4] = {
            {1, 0, 0},
            {1, 3, 3, 1},
            {1, 3},
            {1, 1, 0},
            {1, 1, 0},
            {-1, 1, M_PI}
    };
    double ranges[NUMBER_OF_FUNCTIONS][2] = {
            {-10, 10},
            {-10, 10},
            {1,   10},
            {0,   10},
            {0, M_PI},
            {-10, 10}
    };

    for (int i = 0; i < NUMBER_OF_FUNCTIONS; ++i) {
        printf("%s in range [%.3lf; %.3lf]: %lf\n\n", formulas[i], ranges[i][0], ranges[i][1],
               integrate_iteratively_trapezoid(functions[i], parameters[i], ranges[i][0], ranges[i][1], precision));
    }

    return 0;
}
