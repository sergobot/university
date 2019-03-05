/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <math.h>
#include <float.h>

#include "integrate.h"

double integrate_fixed_steps(integration_method method,
                             mathematical_function f,
                             double left_border,
                             double right_border,
                             unsigned steps_count)
{
    double step = (right_border - left_border) / steps_count;
    double half_step = step / 2;

    double left_x = left_border;
    double middle_x = left_border;
    double right_x = left_border;

    double total_area = 0;
    for (int i = 0; i < steps_count; ++i)
    {
        left_x = right_x;
        middle_x = left_x + half_step;
        right_x += step;

        switch(method)
        {
        case LEFT_RECTANGLES:
            total_area += fabs(f(left_x));
                break;
        case RIGHT_RECTANGLES:
            total_area += fabs(f(right_x));
                break;
        case MIDDLE_RECTANGLES:
            total_area += fabs(f(middle_x));
                break;
        case TRAPEZOIDS:
            total_area += (fabs(f(right_x)) + fabs(f(left_x))) / 2;
                break;
        case PARABOLAS:
            total_area += (fabs(f(right_x)) + 4 * fabs(f(middle_x)) + fabs(f(right_x))) / 6;
                break;
            default:
                /* Internal error, exit with negative area */
                return -1;
        }
    }

    return total_area * step;
}

double integrate_iteratively_trapezoid(mathematical_function f,
                                       double left_border,
                                       double right_border,
                                       double precision) {
    precision = fabs(precision);

    unsigned steps_count = 1;
    double achieved_precision = DBL_MAX;

    unsigned iteration = 0;
    double current_area = 0, previous_area = 0;
    while (achieved_precision > precision) {
        double step = (right_border - left_border) / steps_count;

        double left_x, right_x = iteration % 2 ? left_border + step / 2 : left_border;
        current_area = 0;
        for (int i = 0; i < steps_count; ++i) {
            left_x = right_x;
            right_x += step;

            current_area += (fabs(f(right_x)) + fabs(f(left_x))) * step / 2;
        }

        current_area = (current_area + previous_area) / 2;

        achieved_precision = fabs(current_area - previous_area);
        previous_area = current_area;

        ++iteration;
        if (iteration % 2 == 1)
            steps_count *= 2;
    }

    return current_area;
}