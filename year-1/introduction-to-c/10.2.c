/** Copyright 2018, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "10.2/function_analysis.h"

int main()
{
    double a, b, c;
    printf("Welcome to 10.2! Please enter function's factors (a, b and c):\n");
    if (scanf("%lf%lf%lf", &a, &b, &c) != 3)
    {
        printf("Invalid input: three real numbers expected. Exiting.\n");
        return 1;
    }

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
               "has two complex roots: %lf + %lf*i and %lf - %lf*i.\n", x1, x2, x1, x2);
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
