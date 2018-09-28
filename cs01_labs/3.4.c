#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("Enter a, b and c as per the task:\n");
    int a, b, c;
    if (scanf("%d%d%d", &a, &b, &c) != 3)
    {
        printf("Ambiguous input. Exiting.\n");
        return 1;
    }

    int h = a / c, w = b / c;
    double k = (double)(h * w * c * c) / (double)(a * b);
    printf("%d squares placed\n", h * w);
    printf("Unoccupied area is %d\n", a * b - h * w * c * c);
    printf("%0.3lf%% taken by the squares\n", k);

    return 0;
}
