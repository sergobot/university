/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include "random_generator_provider.h"

RandomGeneratorProvider* RandomGeneratorProvider::singleton = nullptr;

RandomGeneratorProvider::RandomGeneratorProvider(std::random_device::result_type seed) : m_generator(seed) {}

std::mt19937 & RandomGeneratorProvider::get()
{
    if(singleton == nullptr)
    {
        std::random_device rd;
        singleton = new RandomGeneratorProvider(rd());
    }
    return singleton->m_generator;
}

