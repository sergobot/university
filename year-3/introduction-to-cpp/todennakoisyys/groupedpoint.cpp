#include "groupedpoint.h"

GroupedPoint::GroupedPoint(double value, size_t count)
    : m_value(value)
    , m_count(count)
{
}

double GroupedPoint::value() const
{
    return m_value;
}

size_t GroupedPoint::count() const
{
    return m_count;
}
