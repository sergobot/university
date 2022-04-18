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
    GroupedSample(const GroupedPoint *const values, size_t size);
    GroupedSample(const GroupedSample &other);
    GroupedSample(GroupedSample &&other) noexcept;

    ~GroupedSample();

    GroupedSample& operator=(const GroupedSample &other);
    GroupedSample& operator=(GroupedSample &&other) noexcept;

    size_t size() const;
    const GroupedPoint& operator[](size_t i) const;
    size_t count() const;

private:
    size_t m_size;
    GroupedPoint *m_values;
    size_t m_count;

    friend void swap(GroupedSample& lhs, GroupedSample& rhs) noexcept
    {
        std::swap(lhs.m_size, rhs.m_size);
        std::swap(lhs.m_values, rhs.m_values);
        std::swap(lhs.m_count, rhs.m_count);
    }
};

#endif // GROUPEDSAMPLE_H
