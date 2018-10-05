/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Enter a, b and c as per the task:\n");
    double a, b, c;
    if (scanf("%lf%lf%lf", &a, &b, &c) != 3)
    {
        printf("Ambiguous input. Exiting.\n");
        return 1;
    }

    int h = a / c, w = b / c;
    double k = (h * w * c * c) / (a * b);
    printf("%d squares placed\n", h * w);
    printf("Unoccupied area is %0.3lf\n", a * b - h * w * c * c);
    printf("%0.3lf%% taken by the squares\n", k);

    return 0;
}
