/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <math.h>
#include "number_analysis.h"

/** Sum digits of n in base b **/
int digit_sum_in_base(int n, int b)
{
    int s = 0;
    while (n > 0)
    {
        s += n % b;
        n /= b;
    }
    return s;
}

/** Count digits of n in base n **/
int count_digits_in_base(int n, int b)
{
    int c = 0;
    while (n > 0)
    {
        ++c;
        n /= b;
    }
    return c;
}

/** Find out whether n is a palindrome or not **/
int is_palindrome(int n)
{
    int k = 0, m = n;
    while (m > 0)
    {
        k *= 10;
        k += m % 10;
        m /= 10;
    }

    return k == n;
}

/** Find out whether n is a prime number or not **/
int is_prime(int n)
{
    /* 0 and 1 are not prime numbers */
    if (n == 1 || n == 0)
        return 0;

    int k = (int) sqrt(n);
    for (int i = 2; i < k; ++i)
        if (n % i == 0)
            return 0;
    return 1;
}
