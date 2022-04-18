#ifndef CHISQUARECRITERION_H
#define CHISQUARECRITERION_H

#include <cstdlib>

#include "discretedistribution.h"
#include "groupedsample.h"
#include "point.h"

/**
 * @brief The ChiSquareCriterion class computes Chi-Square criterion to determine
 * whether given sample belongs to provided distribution.
 */
class ChiSquareCriterion
{
public:
    ChiSquareCriterion(const DiscreteDistribution &distr, const GroupedSample &sample);
    ~ChiSquareCriterion() noexcept {};

    /**
     * @brief Returns degrees of freedom, if computed. If not, computes them first.
     * @return degrees of freedom.
     */
    long degrees();

    /**
     * @brief Returns chi-square statistic, if computed. If not, computes it first.
     * @return chi-square statistic.
     */
    double chiSquare();

    /**
     * @brief Returns p-value, if computed. If not, computes it first.
     * @return p-value.
     */
    double pValue();

private:
    const long m_states;
    long m_degrees;
    double m_chiSquare;
    double m_pValue;

    /**
     * @brief m_empirical stores empirical counts
     */
    std::vector<GroupedPoint> m_empirical;
    /**
     * @brief m_theoretical stores theoretical counts.
     * Beware, these are probabilites multiplied by sample size.
     */
    std::vector<Point> m_theoretical;

    std::vector<double> m_empirical_merged;
    std::vector<double> m_theoretical_merged;
};

#endif // CHISQUARECRITERION_H
