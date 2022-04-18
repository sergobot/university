#include "groupedsample.h"

GroupedSample::GroupedSample(const GroupedPoint *const values, size_t size)
    : m_size(size)
    , m_values(new GroupedPoint[size])
    , m_count(0)
{
    for (size_t i = 0; i < m_size; ++i)
    {
        m_values[i] = values[i];
        m_count += values[i].count();
    }
}

GroupedSample::GroupedSample(const GroupedSample &other)
    : m_size(other.m_size)
    , m_values(new GroupedPoint[other.size()])
    , m_count(other.m_count)
{
    for (size_t i = 0; i < other.size(); ++i)
        m_values[i] = other[i];
}

GroupedSample::GroupedSample(GroupedSample &&other) noexcept
    : m_size(0)
    , m_values(nullptr)
    , m_count(0)
{
    swap(*this, other);
}

GroupedSample::~GroupedSample()
{
    delete[] m_values;
}

GroupedSample& GroupedSample::operator=(const GroupedSample &other)
{
    GroupedSample copy(other);
    swap(*this, copy);
    return *this;
}

GroupedSample& GroupedSample::operator=(GroupedSample&& other) noexcept
{
    swap(*this, other);
    return *this;
}

size_t GroupedSample::size() const
{
    return m_size;
}

const GroupedPoint& GroupedSample::operator[](size_t i) const
{
    return m_values[i];
}

size_t GroupedSample::count() const
{
    return m_count;
}
