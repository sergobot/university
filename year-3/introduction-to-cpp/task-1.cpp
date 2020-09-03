/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>
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
    double x;
    std::cout << "Enter a number:" << std::endl;
    std::cin >> x;
    std::cout << "if version:      f(" << x << ") = " << compute_function_using_if(x) << std::endl;
    std::cout << "ternary version: f(" << x << ") = " << compute_function_using_ternary(x) << std::endl;

    return 0;
}