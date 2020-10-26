/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>
#include <functional>
#include <random>
#include <iomanip>

int main()
{
    const long X_LOWER_LIMIT = -1, X_UPPER_LIMIT = 1, Y_LOWER_LIMIT = 0, Y_UPPER_LIMIT = 2;
    const long MAX_AREA = (X_UPPER_LIMIT - X_LOWER_LIMIT) * (Y_UPPER_LIMIT - Y_LOWER_LIMIT);

    const double TRUE_AREA = 2.38629436111989;

    std::mt19937 gen;
    gen.seed(11);
    std::uniform_real_distribution<> x_dist(X_LOWER_LIMIT, X_UPPER_LIMIT);
    std::uniform_real_distribution<> y_dist(Y_LOWER_LIMIT, Y_UPPER_LIMIT);

    std::function<double(double)> f = [](double x) { return 0.5 / std::abs(x); };

    std::cout << "Computing area under graph of y = 1 / (2 |x|). x between " << X_LOWER_LIMIT << " and " << X_UPPER_LIMIT
              << ", y between " << Y_LOWER_LIMIT << " and " << Y_UPPER_LIMIT << std::endl;

    size_t checkpoint = 100, max_iter = 1000000;
    size_t got_under_the_graph = 0;
    for (size_t i = 0; i <= max_iter; ++i)
    {
        if (i == checkpoint)
        {
            double result = (double)got_under_the_graph / checkpoint * MAX_AREA;
            std::cout << std::setw(9) << checkpoint << " iterations: " << std::setprecision(10) << std::setw(8)
                      << result << " (error = " << std::setw(8) << std::abs(result - TRUE_AREA) << ")" << std::endl;
            checkpoint *= 100;
        }
        double x = x_dist(gen), y = y_dist(gen);
        if (f(x) >= y)
            ++got_under_the_graph;
    }

}