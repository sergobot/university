#include "tablesamplegenerator.h"
#include "random_generator_provider.h"

TableSampleGenerator::TableSampleGenerator(const GroupedDiscreteDistribution& distribution)
    : SampleGenerator()
    , m_distribution(distribution)
    , m_count(0)
{
    for (size_t i = 0; i < m_distribution.size(); ++i)
        m_count += m_distribution[i].count();
}

/*virtual*/ Sample TableSampleGenerator::generate(size_t size)
{
    double temp[m_count];
    int pointer = 0;
    for (size_t i = 0; i < m_distribution.size(); ++i)
    {
        const GroupedPoint& point = m_distribution[i];
        for (int j = 0; j < point.count(); ++j, ++pointer)
            temp[pointer] = point.value();
    }

    std::mt19937 &engine = RandomGeneratorProvider::get();
    std::uniform_real_distribution<> dis(0, m_count);

    std::vector<double> result = std::vector<double>(size);
    for (size_t i = 0; i < size; ++i)
    {
        double alpha = dis(engine);
        int tau = (int)alpha;
        result[i] = temp[tau];
    }

    return Sample(result);
}
