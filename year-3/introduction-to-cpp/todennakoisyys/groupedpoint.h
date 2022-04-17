#ifndef GROUPEDPOINT_H
#define GROUPEDPOINT_H

#include <cstdlib>

/**
 * @brief The GroupedPoint class stores value and its count in a sample or as
 * a means of specifying a grouped distribution.
 */
class GroupedPoint
{
public:
    GroupedPoint(double value = 0, size_t count = 0);

    double value() const;
    size_t count() const;
private:
    double m_value;
    size_t m_count;
};

#endif // GROUPEDPOINT_H
