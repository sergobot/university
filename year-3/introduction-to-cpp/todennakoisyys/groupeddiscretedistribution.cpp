#include "distribution.h"

DiscreteDistribution::DiscreteDistribution(QVector<Point> points, QObject *parent)
    : QObject(parent)
    , points(points)
{

}

const Point& DiscreteDistribution::operator[](size_t i) const
{
    return points.at(i);
}

const QVector<double>& DiscreteDistribution::getCumProbs() const
{
    return cumprobs;
}

QVector<double> DiscreteDistribution::getTableForN(size_t n) const
{
    QVector<double> result(n);

    double currentValue = points.at(0).value;
    for (int i = 0; i < points.size(); ++i)
    {

    }
}

size_t DiscreteDistribution::size() const
{
    return points.size();
}

void DiscreteDistribution::computeCumProbs()
{
    cumprobs.clear();
    cumprobs.reserve(points.size());

    double sum = 0;
    for (int i = 0; i < points.size(); ++i)
        cumprobs.append(sum += points.at(i).probability);
}
