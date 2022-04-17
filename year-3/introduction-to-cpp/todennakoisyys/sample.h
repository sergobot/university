#ifndef SAMPLE_H
#define SAMPLE_H

#include <vector>
#include "groupedsample.h"

/**
 * @brief The Sample class represents raw results of sampling, being unordered
 * and without any grouping.
 */
class Sample
{
public:
    static const Sample EMPTY(std::vector<double>());

    Sample(std::vector<double> values);

    /**
     * @brief group converts Sample to GroupedSample, grouping and ordering by value.
     * @return
     */
    GroupedSample group() const;

    const std::vector<double> values;
};

#endif // SAMPLE_H
