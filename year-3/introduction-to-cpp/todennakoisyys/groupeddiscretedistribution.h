#ifndef GROUPED_DISCRETE_DISTRIBUTION_H
#define GROUPED_DISCRETE_DISTRIBUTION_H

#include <vector>

#include "groupedpoint.h"
#include "distribution.h"
#include "discretedistribution.h"

/**
 * @brief The GroupedDiscreteDistribution class represents a discrete distribution,
 * specified with the provided in its constructor counts.
 */
class GroupedDiscreteDistribution : public Distribution<GroupedPoint>
{
public:
    explicit GroupedDiscreteDistribution(std::vector<GroupedPoint> groupedPoints);

    size_t size() const override;
    const GroupedPoint& operator[](size_t i) const override;

    /**
     * @brief ungroup converts grouped distribution to a normal one using division
     * of separate counts by the total.
     * @return a new DiscreteDistribution, identical to this.
     */
    DiscreteDistribution ungroup() const;

private:
    std::vector<GroupedPoint> points;
};

#endif // GROUPED_DISCRETE_DISTRIBUTION_H
