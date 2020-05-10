/** Copyright 2018, Sergey Popov (me@sergobot.me) **/

/**
 * Function analysis module
 */

#ifndef FUNCTION_ANALYSIS_H
#define FUNCTION_ANALYSIS_H

typedef enum type
{
    QUADRATIC_TWO_REAL_ROOTS,
    QUADRATIC_ONE_REAL_ROOT,
    QUADRATIC_TWO_COMPLEX_ROOTS,
    LINEAR,
    NO_ROOTS,
    ANY_NUMBER_IS_ROOT,
    FACTOR_IS_INF_OR_NAN
} FunctionType;

/**
 * Analyze a quadratic or linear function and find its roots (if any).
 * @param a - coefficient before x^2
 * @param b - coefficient before x
 * @param c - free term of the function
 * @param x1 - pointer to return one of the roots or the real part of
 *             a complex root
 * @param x2 - pointer to return the other root or the complex part of
 *             a complex root
 * @return Type of the function with given factors a, b, c.
 */
FunctionType analyze_function(double a, double b, double c,
                              double *x1, double *x2);

#endif // FUNCTION_ANALYSIS_H
