/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>
#include <vector>
#include <cmath>

double compute_function_using_if(double x)
{
    if (x > 0)
        return exp(sin(x));
    return exp(x);
}

double compute_function_using_ternary(double x)
{
    return x > 0 ? exp(sin(x)) : exp(x);
}

int main()
{
    const double eps = 1e-8;

    // -1 to cover cases where x < 0
    // 0 to cover the edge case
    // 1 to cover cases where x > 0
    std::vector<std::pair<double, double>> tests = {{-1.5, 0.22313016}, {0.0, 1.0}, {1.3, 2.62100592}};

    for (const auto & test : tests)
    {
        double x = test.first, y = test.second;
        std::cout << "x = " << x << std::endl;
        double ternary = compute_function_using_ternary(x), if_based = compute_function_using_if(x);
        std::cout << "    ternary  f(x) = " << ternary  << (std::abs(ternary  - y) < eps ? " -- [VALID]" : " -- [INVALID]") << std::endl;
        std::cout << "    if-based f(x) = " << if_based << (std::abs(if_based - y) < eps ? " -- [VALID]" : " -- [INVALID]") << std::endl;
    }

    return 0;
}