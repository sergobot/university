/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>
#include <math.h>

int main()
{
    printf("Welcome to 5.9! Please enter a, b and c separated by spaces:\n");
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);

    // Linear equation
    if (a == 0)
    {
        if (b == 0)
        {
            if (c == 0)
            {
                printf("Any real number is a root.\n");
                return 0;
            }
            printf("No roots.\n");
            return 0;
        }

        double x = -(double)c / b;
        printf("Root of the linear equation is %.3lf\n", x);
        return 0;
    }
    // Quadratic equation
    else
    {
        double d = b * b - 4 * a * c;
        if (d > 0)
        {
            d = sqrt(d);
            double x1 = (-b + d) / 2 / a;
            double x2 = (-b - d) / 2 / a;
            printf("Roots of the quadratic equation are %.3lf and %.3lf\n", x1, x2);
        }
        else if (d == 0)
        {
            double x = (double)(-b) / 2 / a;
            printf("The only root of the quadratic equation is %.3lf\n", x);
        }
        else
        {
            d = sqrt(-d);
            double m = (double)(-b) / a / 2;
            double l = d / a / 2;
            printf("Complex roots of the quadratic equation are %.3lf + %.3lf * i and %.3lf - %.3lf * i\n",
            m, l, m, l);
        }
    }

    return 0;
}
