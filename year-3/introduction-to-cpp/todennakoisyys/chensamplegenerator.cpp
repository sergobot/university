#include "chensamplegenerator.h"
#include "random_generator_provider.h"

ChenSampleGenerator::ChenSampleGenerator(const DiscreteDistribution& distr, size_t windows)
    : SampleGenerator()
    , m_distribution(distr)
    , m_windows(windows)
{
}

/*virtual*/ Sample ChenSampleGenerator::generate(size_t size)
{
    double cumProbs[m_distribution.size()], temp[m_windows];

    cumProbs[0] = m_distribution[0].probability();
    for (size_t i = 1; i < m_distribution.size(); ++i)
        cumProbs[i] = cumProbs[i - 1] + m_distribution[i].probability();

    for (size_t j = 0; j < m_windows; ++j)
    {
        size_t i = 0;
        for (; i < m_distribution.size(); ++i)
             if (cumProbs[i] * m_windows > j)
                 break;
        temp[j] = i;
    }

    std::mt19937 &engine = RandomGeneratorProvider::get();
    std::uniform_real_distribution<> dis(0, 1);

    std::vector<double> result(size);
    for (size_t i = 0; i < size; ++i)
    {
        double alpha = dis(engine);
        size_t j = (size_t)(m_windows * alpha);
        size_t h = temp[j];
        while (alpha > cumProbs[h]) ++h;
        result[i] = m_distribution[h].value();
    }

    return Sample(result);
}
