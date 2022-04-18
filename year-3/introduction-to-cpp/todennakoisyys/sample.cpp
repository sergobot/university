#include <map>
#include <algorithm>

#include "sample.h"

Sample::Sample(const double *const values, size_t size)
    : m_size(size)
    , m_values(new double[size])
{
    for (size_t i = 0; i < m_size; ++i)
        m_values[i] = values[i];
}

Sample::Sample(const Sample &other)
    : m_size(other.m_size)
    , m_values(new double[other.m_size])
{
    for (size_t i = 0; i < other.size(); ++i)
        m_values[i] = other[i];
}

Sample::Sample(Sample &&other) noexcept
    : m_size(0)
    , m_values(nullptr)
{
    swap(*this, other);
}

Sample::~Sample()
{
    delete[] m_values;
}

Sample& Sample::operator=(const Sample &other)
{
    Sample copy(other);
    swap(*this, copy);
    return *this;
}

Sample& Sample::operator=(Sample &&other) noexcept
{
    swap(*this, other);
    return *this;
}

const double& Sample::operator[](size_t i) const
{
    return m_values[i];
}

size_t Sample::size() const
{
    return m_size;
}

GroupedSample Sample::group() const
{
    std::map<double, size_t> counts;
    for (size_t i = 0; i < m_size; ++i)
    {
        std::map<double, size_t>::iterator it(counts.find(m_values[i]));
        if (it != counts.end()){
           it->second++;
        } else {
           counts[m_values[i]] = 1;
        }
    }

    size_t valuesSize = counts.size();
    GroupedPoint groupedValues[valuesSize];

    size_t i = 0;
    for (const auto& pair : counts)
        groupedValues[i++] = GroupedPoint(pair.first, pair.second);

    std::sort(groupedValues, groupedValues,
              [](const GroupedPoint& a, const GroupedPoint& b) { return a.value() < b.value(); });

    return GroupedSample(groupedValues, valuesSize);
}
