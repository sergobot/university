/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>
#include "10.1/number_analysis.h"

int main()
{
    int n, b;
    printf("Welcome to 10.1! Please enter a number and numeral system base:\n");
    if (scanf("%d%d", &n, &b) != 2)
    {
        printf("Invalid input: two natural numbers expected. Exiting.\n");
        return 1;
    }

    printf("Sum of digits of %d in base %d is %d;\n"
           "There are %d digits in %d in base %d;\n"
           "%d is%s a palindrome;\n"
           "%d is%s a prime number.\n",
           n, b, digit_sum_in_base(n, b),
           count_digits_in_base(n, b), n, b,
           n, is_palindrome(n) ? "" : " not",
           n, is_prime(n) ? "" : " not");

    return 0;
}
