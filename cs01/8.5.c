/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>

/*
 * sqrt computes sqare root of a number with given accuracy.
 * if the number or accuracy is negative, returns -1;
 */
double my_sqrt(double a, double accuracy);

/*
 * Returns an absolute value of a;
 */
double my_abs(double a);

int main()
{
    double a, accuracy;

    printf("Enter a number:\n");
    if (scanf("%lf", &a) != 1)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    printf("Enter the accuracy (epsilon):\n");
    if (scanf("%lf", &accuracy) != 1)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    printf("Square root of %lf, computed with accuracy %lf is %lf\n",
           a, accuracy, my_sqrt(a, accuracy));

    return 0;
}

double my_sqrt(double a, double accuracy)
{
    double x = a, x_prev;

    if (a < 0 || accuracy <= 0)
        return 0.0/0.0;

    if (a == 1.0/0.0)
        return a;

    do
    {
        x_prev = x;
        x = (x_prev + a / x_prev) / 2;
    } while (my_abs((x - x_prev) / x) >= accuracy);

    return x;
}

double my_abs(double a)
{
    return a >= 0 ? a : -a;
}
