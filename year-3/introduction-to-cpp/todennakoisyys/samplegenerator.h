#ifndef SAMPLEGENERATOR_H
#define SAMPLEGENERATOR_H

#include "distribution.h"
#include "sample.h"

/**
 * @brief The SampleGenerator class provides a common ground for several sample generators,
 * using different mathematical methods.
 */
template<typename TDistribution>
class SampleGenerator
{
public:
    virtual Sample generate(size_t size) = 0;
};

#endif // SAMPLEGENERATOR_H
