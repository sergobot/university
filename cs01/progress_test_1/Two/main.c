/** Copyright Sergey Popov (me@sergobot.me), 2018 **/

#include <stdio.h>
#include <stdlib.h>\

#include "hypercosine.h"

int main()
{
    double x = 0, e = 0;
    printf("Welcome to Two by Sergobot! Please enter x and epsilon:\n");
    if (scanf("%lf%lf", &x, &e) != 2)
    {
        printf("Invalid input: expected two real numbers! Exiting.\n");
        return 1;
    }

    int c;
    double cosh = hypercosine(x, e, &c);

    printf("Hyperbolic cosine of %lf with precision %lf, computed in %d steps is %lf\n",
           x, e, c, cosh);

    return 0;
}
