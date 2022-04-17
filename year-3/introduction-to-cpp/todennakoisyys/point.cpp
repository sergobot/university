#include "point.h"

Point::Point(double value, double probability)
    : m_value(value)
    , m_probability(probability)
{
}

double Point::value() const
{
    return m_value;
}

double Point::probability() const
{
    return m_probability;
}
