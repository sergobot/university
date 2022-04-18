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
    Sample(const double *const values, size_t size);
    Sample(const Sample &other);
    Sample(Sample &&other) noexcept;

    ~Sample();

    Sample& operator=(const Sample &other);
    Sample& operator=(Sample &&other) noexcept;

    size_t size() const;
    const double& operator[](size_t i) const;

    /**
     * @brief group converts Sample to GroupedSample, grouping and ordering by value.
     * @return
     */
    GroupedSample group() const;

private:
    size_t m_size;
    double *m_values;

    friend void swap(Sample& lhs, Sample& rhs) noexcept
    {
        std::swap(lhs.m_size, rhs.m_size);
        std::swap(lhs.m_values, rhs.m_values);
    }
};

#endif // SAMPLE_H
