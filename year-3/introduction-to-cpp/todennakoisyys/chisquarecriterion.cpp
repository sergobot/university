#include <cmath>
#include <iostream>

#include "3rdparty/probdist.h"
#include "chisquarecriterion.h"

ChiSquareCriterion::ChiSquareCriterion(const DiscreteDistribution &distr, const GroupedSample &sample)
    : m_states(distr.size())
    , m_degrees(-1)
    , m_chiSquare(-1)
    , m_pValue(-1)
{
    m_theoretical.resize(m_states);
    for (size_t i = 0; i < m_states; ++i)
        m_theoretical.at(i) = Point(distr[i].value(), distr[i].probability() * sample.count());

    m_empirical.resize(m_states);
    for (size_t i = 0, j = 0; i < m_states; ++i, ++j)
    {
        while (i < m_states && distr[i].value() != sample.values().at(i).value())
        {
            m_empirical.at(i) = GroupedPoint(distr[i].value(), 0);
            ++i;
        }
        m_empirical.at(i) = sample.values().at(j);
    }
    m_empirical_merged.resize(m_states);
    m_theoretical_merged.resize(m_states);
}

long ChiSquareCriterion::degrees()
{
    if (m_degrees < 0)
    {
        m_degrees = 0;
        for (size_t i = 0; i < m_states; ++i, ++m_degrees)
        {
            for (m_empirical_merged.at(m_degrees) = 0, m_theoretical_merged.at(m_degrees) = 0;
                 i < m_states && m_theoretical_merged.at(m_degrees) < 5;
                 ++i)
            {
                if (m_degrees < 0 || m_degrees >= m_states || i < 0 || i >= m_states)
                {
                    std::cout << "SHIT DETECTED i=" << i << ", m_degrees=" << m_degrees << std::endl;
                }
                m_empirical_merged.at(m_degrees) += m_empirical.at(i).count();
                m_theoretical_merged.at(m_degrees) += m_theoretical.at(i).probability();
            }

            if (m_theoretical_merged.at(m_degrees) < 5)
            {
                if (m_degrees < 0 || m_degrees >= m_states || i < 0 || i >= m_states)
                {
                    std::cout << "SHIT DETECTED i=" << i << ", m_degrees=" << m_degrees << std::endl;
                }
                m_empirical_merged.at(m_degrees - 1) += m_empirical_merged.at(m_degrees);
                m_theoretical_merged.at(m_degrees - 1) += m_theoretical_merged.at(m_degrees);
                --m_degrees;
                if (m_degrees < 0 || m_degrees >= m_states || i < 0 || i >= m_states)
                {
                    std::cout << "SHIT DETECTED i=" << i << ", m_degrees=" << m_degrees << std::endl;
                }
            }
            --i;
            if (m_degrees < 0 || m_degrees >= m_states || i < 0 || i >= m_states)
            {
                std::cout << "SHIT DETECTED i=" << i << ", m_degrees=" << m_degrees << std::endl;
            }
        }
        if (m_degrees < 0 || m_degrees >= m_states)
        {
            std::cout << "SHIT DETECTED m_degrees=" << m_degrees << std::endl;
        }
    }
    return m_degrees;
}

double ChiSquareCriterion::chiSquare()
{
    if (m_chiSquare < 0)
    {
        // ensure degrees are calculated
        degrees();

        m_chiSquare = 0;
        for (size_t i = 0; i < m_degrees; ++i)
        {
            m_chiSquare += std::pow(m_empirical_merged[i] - m_theoretical_merged[i], 2) / m_theoretical_merged[i];
        }
    }
    return m_chiSquare;
}


double ChiSquareCriterion::pValue()
{
    if (m_pValue < 0)
        m_pValue = 1 - pChi(chiSquare(), degrees());
    return m_pValue;
}
