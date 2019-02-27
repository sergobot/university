/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "13/integrate.h"

double f(double x)
{
    return 10;
}

int main()
{
    printf("%lf\n", integrate_fixed_steps(LEFT_RECTANGLES, f, -5, 5, 1000));
    printf("%lf\n", integrate_fixed_steps(MIDDLE_RECTANGLES, f, -5, 5, 1000));
    printf("%lf\n", integrate_fixed_steps(RIGHT_RECTANGLES, f, -5, 5, 1000));
}
