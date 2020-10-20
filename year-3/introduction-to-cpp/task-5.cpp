/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>
#include <functional>
#include <random>

int main()
{
    const long X_LOWER_LIMIT = -1, X_UPPER_LIMIT = 1, Y_LOWER_LIMIT = 0, Y_UPPER_LIMIT = 2;
    const long MAX_AREA = (X_UPPER_LIMIT - X_LOWER_LIMIT) * (Y_UPPER_LIMIT - Y_LOWER_LIMIT);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> x_dist(X_LOWER_LIMIT, X_UPPER_LIMIT);
    std::uniform_real_distribution<> y_dist(Y_LOWER_LIMIT, Y_UPPER_LIMIT);

    std::function<double(double)> f = [](double x) { return 0.5 / std::abs(x); };

    std::cout << "Computing area under graph of y = 1 / (2 |x|). x between " << X_LOWER_LIMIT << " and " << X_UPPER_LIMIT
              << ", y between " << Y_LOWER_LIMIT << " and " << Y_UPPER_LIMIT << std::endl;

    size_t iterations;
    std::cout << "Please enter number of iterations: ";
    std::cin >> iterations;

    size_t got_under_the_graph = 0;
    for (size_t i = 0; i < iterations; ++i)
    {
        double x = x_dist(gen), y = y_dist(gen);
        if (f(x) >= y)
            ++got_under_the_graph;
    }

    std::cout << "Computed area is " << (double)got_under_the_graph / iterations * MAX_AREA << std::endl;
}