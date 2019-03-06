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

// Should compute a mathematical function in given point.
// x is the point, p is an array of parameters.
typedef double (*mathematical_function) (double x, double *p);

double integrate_fixed_steps(integration_method method,
                             mathematical_function f,
                             double *p,
                             double left_border,
                             double right_border,
                             unsigned dots);

double integrate_iteratively_trapezoid(mathematical_function f,
                                       double *p,
                                       double left_border,
                                       double right_border,
                                       double precision);

#endif // INTEGRATE_H
