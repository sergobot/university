/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef INTEGRATE_H
#define INTEGRATE_H

typedef enum method
{
    LEFT_RECTANGLES,
    RIGHT_RECTANGLES,
    MIDDLE_RECTANGLES,
    TRAPEZOIDS,
    PARABOLAS
} integration_method;
typedef double (*mathematical_function) (double x);

double integrate_fixed_steps(integration_method method,
                             mathematical_function f,
                             double left_border,
                             double right_border,
                             unsigned dots);

double integrate_iteratively_trapezoid(mathematical_function f,
                                       double left_border,
                                       double right_border,
                                       double precision);

#endif // INTEGRATE_H
