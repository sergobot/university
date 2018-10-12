/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>

int main()
{
    double a, b, h;
    printf("Welcome to 7.5! Please enter the beginning and the end of the interval (a and b):\n");
    if (scanf("%lf%lf", &a, &b) != 2)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    printf("Now please enter step (h):\n");
    if (scanf("%lf", &h) != 1)
    {
        printf("Invalid input. Exiting.\n");
        return 1;
    }

    printf("\ny = x^2 + 2x - 3 in [%.3lf, %.3lf] with step %.3lf\nx\ty\n", a, b, h);
    for (; a <= b; a += h)
        printf("%.3lf\t%.3lf\n", a, a * a  + 2 * a - 3);

    return 0;
}
