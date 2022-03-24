#include "tablesamplegenerator.h"
#include "random_generator_provider.h"

TableSampleGenerator::TableSampleGenerator(QObject *parent)
    : SampleGenerator(parent)
{
}

/*virtual*/ Sample generate(DiscreteDistribution* distr, size_t size)
{
    QVector<double> cumprobs = distr->getOrComputeCumulativeProbs();

    std::mt19937 engine = RandomGeneratorProvider::get();
    std::uniform_real_distribution<> dis(1.0, 2.0);

    QVector<double> result = QVector<double>(size);
    for (size_t i = 0; i < size; ++i) {
        double val = dis(engine);
        for
    }
    return Sample(result);
}
