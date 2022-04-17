#ifndef DISCRETEDISTRIBUTION_H
#define DISCRETEDISTRIBUTION_H

#include <vector>
#include <cstdlib>

#include "distribution.h"
#include "point.h"

/**
 * @brief The DiscreteDistribution class represents a generic discrete distribution,
 * as per the provided in its constructor points.
 */
class DiscreteDistribution : public Distribution<Point>
{
public:
    DiscreteDistribution(const std::vector<Point>& points);

    size_t size() const override;
    const Point& operator[](size_t i) const override;

private:
    std::vector<Point> points;
};

#endif // DISCRETEDISTRIBUTION_H
