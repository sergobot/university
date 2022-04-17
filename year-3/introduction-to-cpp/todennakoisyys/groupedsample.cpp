#include "groupedsample.h"

const GroupedSample GroupedSample::EMPTY = GroupedSample(std::vector<GroupedPoint>());

GroupedSample::GroupedSample(std::vector<GroupedPoint> values)
    : m_values(values)
    , m_count(0)
{
    for (const auto& p : values)
        m_count += p.count();
}


const std::vector<GroupedPoint>& GroupedSample::values() const
{
    return m_values;
}

size_t GroupedSample::count() const
{
    return m_count;
}
