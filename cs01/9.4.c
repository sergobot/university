/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>
#include <math.h>

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

FunctionType analyze_function(double a, double b, double c,
                              double *x1, double *x2);

int main()
{
    double a, b, c;

    printf("Welcome to 9.4! Enter function factors (a, b and c):\n");
    if (scanf("%lf%lf%lf", &a, &b, &c) != 3)
    {
        printf("Invalid input. Exiting.\n");
        return -1;
    }

    printf("\nResults of function analysis:\n");

    double x1, x2;
    switch(analyze_function(a, b, c, &x1, &x2))
    {
    case QUADRATIC_TWO_REAL_ROOTS:
        printf("The function is quadratic and "
               "has two real roots %lf and %lf\n.", x1, x2);
        break;
    case QUADRATIC_ONE_REAL_ROOT:
        printf("The function is quadratic and "
               "has one real root %lf\n.", x1);
        break;
    case QUADRATIC_TWO_COMPLEX_ROOTS:
        printf("The function is quadratic and "
               "has two complex roots.\n");
        break;
    case LINEAR:
        printf("The function is linear and "
               "the root is %lf.\n", x1);
        break;
    case NO_ROOTS:
        printf("The function has no roots.\n");\
        break;
    case ANY_NUMBER_IS_ROOT:
        printf("The function has an infinite number "
               "of roots (any number is a root)\n");
        break;
    case FACTOR_IS_INF_OR_NAN:
        printf("One of the function's factors "
               "is either infinity or not a number.\n");
        break;
    default:
        printf("Unexpected function type. "
               "Please contact the developer.\n");
        return -1;
    }

    return 0;
}

FunctionType analyze_function(double a, double b, double c,
                              double *x1, double *x2)
{
    if (isnan(a) || isnan(b) || isnan(c) ||
        isinf(a) || isinf(b) || isinf(c))
            return FACTOR_IS_INF_OR_NAN;

    if (a == 0 && b == 0 && c == 0)
        return ANY_NUMBER_IS_ROOT;

    if (a == 0 && b == 0)
        return NO_ROOTS;

    if (a == 0)
    {
        *x1 = *x2 = -c / b;
        return LINEAR;
    }

    // So far, a is not a zero but b and c may be.
    double d = b * b - 4 * a * c;

    if (d < 0)
        return QUADRATIC_TWO_COMPLEX_ROOTS;

    if (d == 0)
    {
        *x1 = *x2 = -b / 2 / a;
        return QUADRATIC_ONE_REAL_ROOT;
    }

    *x1 = (-b + sqrt(d)) / 2 / a;
    *x2 = (-b - sqrt(d)) / 2 / a;
    return QUADRATIC_TWO_REAL_ROOTS;
}
