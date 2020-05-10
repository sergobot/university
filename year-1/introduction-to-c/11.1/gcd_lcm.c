/** Copyright 2018, Sergey Popov (me@sergobot.me) **/

#include "gcd_lcm.h"

/** Compute Greatest Common Divisor of two numbers iteratively **/
int gcd_iterative(int a, int b)
{
    int t;
    while (b > 0)
    {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

/** Compute Greatest Common Divisor of two numbers recursively **/
int gcd_recursive(int a, int b)
{
    return a % b == 0 ? b : gcd_recursive(b, a % b);
}

/** Compute Least Common Multiple of two numbers iteratively **/
int lcm_iterative(int a, int b)
{
    return a * b / gcd_iterative(a, b);
}

/** Compute Least Common Multiple of two numbers recursively **/
int lcm_recursive(int a, int b)
{
    return a * b / gcd_recursive(a, b);
}
