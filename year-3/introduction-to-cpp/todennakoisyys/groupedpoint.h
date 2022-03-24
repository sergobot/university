#ifndef GROUPEDPOINT_H
#define GROUPEDPOINT_H

#include <cstdlib>

class GroupedPoint
{
public:
    GroupedPoint(double value = 0, size_t count = 0);

    const double value;
    const size_t count;
};

#endif // GROUPEDPOINT_H
