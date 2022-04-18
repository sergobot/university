#include "discretedistribution.h"

DiscreteDistribution::DiscreteDistribution(const std::vector<Point> &points)
    : points(points)
{
}

size_t DiscreteDistribution::size() const
{
    return points.size();
}

const Point& DiscreteDistribution::operator[](size_t i) const
{
    return points.at(i);
}

//const std::vector<double>& DiscreteDistribution::getCumProbs() const
//{
//    return cumProbs;
//}

//std::vector<double> DiscreteDistribution::getTableForN(size_t n) const
//{
//    std::vector<double> result(n);

//    double currentValue = points.at(0).value;
//    for (int i = 0; i < points.size(); ++i)
//    {

//    }
//}

//void DiscreteDistribution::computeCumProbs()
//{
//    cumProbs.clear();
//    cumProbs.reserve(points.size());

//    double sum = 0;
//    for (int i = 0; i < points.size(); ++i)
//        cumProbs.append(sum += points.at(i).probability);
//}
