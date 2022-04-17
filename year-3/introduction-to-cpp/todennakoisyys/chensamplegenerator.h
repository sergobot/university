#ifndef CHENSAMPLEGENERATOR_H
#define CHENSAMPLEGENERATOR_H

#include "samplegenerator.h"
#include "discretedistribution.h"

/**
 * @brief The ChenSampleGenerator class generates sample using Chen's method.
 */
class ChenSampleGenerator : public SampleGenerator<DiscreteDistribution>
{
public:
    ChenSampleGenerator(const DiscreteDistribution& distribution, size_t windows);

    /**
     *  @brief Generates sample of given size.
     */
    Sample generate(size_t size) override;

private:
    DiscreteDistribution m_distribution;
    size_t m_windows;
};

#endif // CHENSAMPLEGENERATOR_H
