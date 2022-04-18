#include "groupeddiscretedistribution.h"

GroupedDiscreteDistribution::GroupedDiscreteDistribution(std::vector<GroupedPoint> groupedPoints)
    : points(groupedPoints)
{

}

size_t GroupedDiscreteDistribution::size() const
{
    return points.size();
}

const GroupedPoint& GroupedDiscreteDistribution::operator[](size_t i) const
{
    return points.at(i);
}

DiscreteDistribution GroupedDiscreteDistribution::ungroup() const
{
    size_t sum = 0;
    for (size_t i = 0; i < points.size(); ++i)
        sum += points[i].count();

    std::vector<Point> result(points.size());
    for (size_t i = 0; i < points.size(); ++i)
        result[i] = Point(points[i].value(), points[i].count() / (double)sum);

    return DiscreteDistribution(result);
}
