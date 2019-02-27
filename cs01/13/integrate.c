/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "integrate.h"
#include "math.h"

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
        case RIGHT_RECTANGLES:
            total_area += fabs(f(right_x));
        case MIDDLE_RECTANGLES:
            total_area += fabs(f(middle_x));
        case TRAPEZOIDS:
            total_area += (fabs(f(right_x)) + fabs(f(left_x))) / 2;
        case PARABOLAS:
            total_area += (f(right_x) + 4 * f(middle_x) + f(right_x)) / 6;
        }
    }

    return total_area * step;
}
