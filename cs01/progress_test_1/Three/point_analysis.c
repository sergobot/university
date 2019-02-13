/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#include "point_analysis.h"

PointPosition analyze_point(double x, double y)
{
    if ( x != x || y != y)
            return UNDEFINED;

    if (x == 0)
    {
        if (y == 0)
            return ZERO;
        else if (y > 0)
            return Y_POSITIVE;
        else
            return Y_NEGATIVE;
    } else if (x > 0) {
        if (y == 0)
            return X_POSITIVE;
        else if (y > 0)
            return QUADRANT_1;
        else
            return QUADRANT_4;
    } else {
        if (y == 0)
            return X_NEGATIVE;
        else if (y > 0)
            return QUADRANT_2;
        else
            return QUADRANT_3;
    }
}
