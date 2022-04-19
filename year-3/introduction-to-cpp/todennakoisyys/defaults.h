#ifndef DEFAULTS_H
#define DEFAULTS_H

#include <vector>

#include "distribution.h"
#include "groupeddiscretedistribution.h"
#include "chensamplegenerator.h"
#include "tablesamplegenerator.h"

/**
 * @file defaults.h contains the defauld distributions and generators
 * used on startup and provided as a beginning point for the user to
 * try out the program.
 */

static const std::vector<GroupedPoint> DEFAULT_POINTS {
                    GroupedPoint(1, 5),
                    GroupedPoint(2, 7),
                    GroupedPoint(3, 80),
                    GroupedPoint(4, 3),
                    GroupedPoint(5, 5)
};

static const GroupedDiscreteDistribution DEFAULT_GROUPED_DISCRETE_DISTRIBUTION(DEFAULT_POINTS);

static const DiscreteDistribution DEFAULT_DISCRETE_DISTRIBUTION =
        DEFAULT_GROUPED_DISCRETE_DISTRIBUTION.ungroup();

static const TableSampleGenerator DEFAULT_TABLE_SAMPLE_GENERATOR(DEFAULT_GROUPED_DISCRETE_DISTRIBUTION);

static const ChenSampleGenerator DEFAULT_CHEN_SAMPLE_GENERATOR(DEFAULT_DISCRETE_DISTRIBUTION, 3);

static const size_t P_VALUE_COUNTS = 10000;

#endif // DEFAULTS_H
