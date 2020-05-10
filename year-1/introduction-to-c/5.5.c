/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>

int main()
{
    printf("Welcome to 5.5! Please enter sides of the first triangle:\n");
    int a, b, c, k, l, m;
    scanf("%d%d%d", &a, &b, &c);
    if (a + b <= c || a + c <= b || b + c <= a)
    {
        printf("Invalid triangle! Exiting.");
        return 1;
    }

    printf("Enter sides of the second triangle:\n");
    scanf("%d%d%d", &k, &l, &m);
    if (k + l <= m || k + m <= l || l + m <= k)
    {
        printf("Invalid triangle! Exiting.");
        return 1;
    }

    // Sort (a, b, c)
    if (c > b)
    {
        b = c - b;
        c = c - b;
        b = c + b;
    }
    if (b > a)
    {
        a = b - a;
        b = b - a;
        a = b + a;
    }
    if (c > b)
    {
        b = c - b;
        c = c - b;
        b = c + b;
    }

    // Sort (k, l, m)
    if (m > l)
    {
        l = m - l;
        m = m - l;
        l = m + l;
    }
    if (l > k)
    {
        k = l - k;
        l = l - k;
        k = l + k;
    }
    if (m > l)
    {
        l = m - l;
        m = m - l;
        l = m + l;
    }

    double x, y, z;
    x = (double)a / k;
    y = (double)b / l;
    z = (double)c / m;

    printf(x == y && y == z ? "The triangles are similar.\n"
                            : "The triangles are not similar.\n"
          );

    return 0;
}
