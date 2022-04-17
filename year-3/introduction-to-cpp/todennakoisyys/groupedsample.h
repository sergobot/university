#ifndef GROUPEDSAMPLE_H
#define GROUPEDSAMPLE_H

#include <vector>
#include "groupedpoint.h"

/**
 * @brief The GroupedSample class stores sampling results in a grouped-by-value
 * manner.
 */
class GroupedSample
{
public:
    static const GroupedSample EMPTY;

    GroupedSample(std::vector<GroupedPoint> values);

    const std::vector<GroupedPoint>& values() const;
    size_t count() const;
private:
    std::vector<GroupedPoint> m_values;
    size_t m_count;
};

#endif // GROUPEDSAMPLE_H
