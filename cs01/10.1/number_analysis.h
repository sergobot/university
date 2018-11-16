/* Copyright 2018, Sergey Popov (me@sergobot.me) */

/**
 * Number analysis module
 */

#ifndef NUMBER_ANALYSIS_H
#define NUMBER_ANALYSIS_H

/**
 * Sum all the number's digits in numeral system with arbitrary base.
 * @param n - the number.
 * @param b - base of the numeral system.
 * @return Sum of n's digits.
 */
int digit_sum_in_base(int n, int b);

/**
 * Count digits of a number in a specific base.
 * @param n - the number.
 * @param b - base of the numeral system.
 * @return Number of digits in n.
 */
int count_digits_in_base(int n, int b);

/**
 * Find out whether a number is a palindrome or not.
 * @param n - the number.
 * @return 1 if n is a palindrome, otherwise 0.
 */
int is_palindrome(int n);

/**
 * Find out whether n is a prime number or not.
 * @param n - the number.
 * @return 1 if n is a prime number, otherwise 0.
 */
int is_prime(int n);

#endif // NUMBER_ANALYSIS_H
