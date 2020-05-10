/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>

int main()
{
    double a, b, h, p;
    printf("Welcome to 7.6! Please enter the beginning and the end of the interval (a and b):\n");
    if (scanf("%lf%lf", &a, &b) != 2)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    printf("Now enter the step (h):\n");
    if (scanf("%lf", &h) != 1)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    printf("This is the last one! Enter p:\n");
    if (scanf("%lf", &p) != 1)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    printf("\ny = (x^2 - p^2)/(x - p) - p in [%.3lf, %.3lf] with step %.3lf and p = %lf\nx\ty\n", a, b, h, p);
    for (; a <= b; a += h)
        if (a != p)
            printf("%.3lg\t%.3lg\n", a, (a * a - p * p) / (a - p) - p);
        else
            printf("%.3lg\tNaN\n", a);
}
