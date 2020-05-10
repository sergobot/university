/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

/** This module provides two functions to compute Chebishev's polynomial:
 * A recursive function
 * An iterative function
**/

#ifndef CHEBYSHEV_H_INCLUDED
#define CHEBYSHEV_H_INCLUDED

/* Computes Chebyshev's polynomial of nth order in point x (recursively) */
double chebishev_recursive(double x, int n);

/* Computes Chebyshev's polynomial of nth order in point x (iteratively) */
double chebishev_iterative(double x, int n);

#endif // CHEBYSHEV_H_INCLUDED
