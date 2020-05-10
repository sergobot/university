/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#include <stdio.h>
#include <stdlib.h>

#include "point_analysis.h"

int main()
{
    double x = 0, y = 0;

    printf("Welcome to Three by Sergobot! Enter coordinates of a point:\n");
    if (scanf("%lf%lf", &x, &y) != 2)
    {
        printf("Invalid input: expected two real numbers. Exiting.\n");
        return 1;
    }

    switch (analyze_point(x, y))
    {
    case UNDEFINED:
        printf("Position is undefined: one of coordinates is NaN.\n");
        break;
    case ZERO:
        printf("The point is at the beginning of the coordinates.\n");
        break;
    case X_POSITIVE:
        printf("The point is at the X axis, on its positive side.\n");
        break;
    case X_NEGATIVE:
        printf("The point is at the X axis, on its negative side.\n");\
        break;
    case Y_POSITIVE:
        printf("The point is at the Y axis, on its positive side.\n");
        break;
    case Y_NEGATIVE:
        printf("The point is at the Y axis, on its negative side.\n");\
        break;
    case QUADRANT_1:
        printf("The point is on the first quadrant.\n");
        break;
    case QUADRANT_2:
        printf("The point is on the second quadrant.\n");
        break;
    case QUADRANT_3:
        printf("The point is on the third quadrant.\n");
        break;
    case QUADRANT_4:
        printf("The point is on the fourth quadrant.\n");
        break;
    default:
        printf("Internal error: please contact the developer.");
        break;
    }

    return 0;
}
