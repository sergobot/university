/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#ifndef HYPERCOSINE_H_INCLUDED
#define HYPERCOSINE_H_INCLUDED

/**
 * Returns cosh(x) with given precision epsilon.
 * Also returns number of additives through *count.
**/
double hypercosine(double x, double epsilon, int *count);

#endif // HYPERCOSINE_H_INCLUDED
