/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#ifndef POINT_ANALYSIS_H_INCLUDED
#define POINT_ANALYSIS_H_INCLUDED

typedef enum PointPosition {
    ZERO,
    X_POSITIVE,
    X_NEGATIVE,
    Y_POSITIVE,
    Y_NEGATIVE,
    QUADRANT_1,
    QUADRANT_2,
    QUADRANT_3,
    QUADRANT_4,
    UNDEFINED
} PointPosition;

PointPosition analyze_point(double x, double y);

#endif // POINT_ANALYSIS_H_INCLUDED
