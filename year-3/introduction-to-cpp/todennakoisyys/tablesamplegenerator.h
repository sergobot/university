#ifndef TABLESAMPLEGENERATOR_H
#define TABLESAMPLEGENERATOR_H

#include "samplegenerator.h"
#include "groupeddiscretedistribution.h"

/**
 * @brief The TableSampleGenerator class performs simulating a distribution using the simplest
 * table method.
 */
class TableSampleGenerator : public SampleGenerator<GroupedDiscreteDistribution>
{
public:
    TableSampleGenerator(const GroupedDiscreteDistribution& distribution);

    /**
     *  @brief Generates sample of given size.
     */
    Sample generate(size_t size) override;

private:
    GroupedDiscreteDistribution m_distribution;
    size_t m_count;
};

#endif // TABLESAMPLEGENERATOR_H
