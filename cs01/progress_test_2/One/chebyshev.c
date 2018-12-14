/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#include "chebyshev.h"

/* Computes Chebyshev's polynomial of nth order in point x (recursively) */
double chebishev_recursive(double x, int n)
{
    if (n == 0) return 1.;
    if (n == 1) return 2*x;

    return 2*x*chebishev_recursive(x, n - 1) - chebishev_recursive(x, n - 2);
}

/* Computes Chebyshev's polynomial of nth order in point x (iteratively) */
double chebishev_iterative(double x, int n)
{
    if (n == 0) return 1.;
    if (n == 1) return 2 * x;

    double un, un1 = 2 * x, un2 = 1.;

    for (int i = 2; i <= n; ++i)
    {
        un = 2 * x * un1 - un2;

        un2 = un1;
        un1 = un;
    }

    return un;
}
