#ifndef POINT_H
#define POINT_H

/**
 * @brief The Point class stores value and its probability in a sample or as
 * a means of specifying a distribution.
 */
class Point
{
public:
    Point(double value = 0, double probability = 0);

    double value() const;
    double probability() const;
private:
    double m_value;
    double m_probability;
};

#endif // POINT_H
