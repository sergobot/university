/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#ifndef HERAKLIO_RANDOM_H
#define HERAKLIO_RANDOM_H

#include <random>

class RandomGeneratorProvider
{
public:
    static std::mt19937& get();

private:
    static RandomGeneratorProvider *singleton;
    RandomGeneratorProvider(std::random_device::result_type seed);

    std::mt19937 m_generator;
};

#endif //HERAKLIO_RANDOM_H
