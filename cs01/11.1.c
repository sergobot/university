/** Copyright 2018, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>

/** Compute digital root of a number in given base **/
int digital_root_recursive(int a, int base);

/** Compute Greatest Common Divisor of two numbers iteratively **/
int gcd_iterative(int a, int b);

/** Compute Greatest Common Divisor of two numbers recursively **/
int gcd_recursive(int a, int b);

/** Compute Least Common Multiple of two numbers iteratively **/
int lcm_iterative(int a, int b);

/** Compute Least Common Moltiple of two numbers recursively **/
int lcm_recursive(int a, int b);

int main()
{
    printf("Welcome to 11.1! Please choose what to compute (1, 2 or 3):\n"
           "1) Digital root in given base\n"
           "2) Greatest Common Divisor\n"
           "3) Lease Common Multiple\n");

    int operation, a, b;
    if (scanf("%d", &operation) != 1 || operation < 1 || operation > 3)
    {
        printf("Invalid input: expected one number between 1 and 3. Exiting.\n");
        return 1;
    }

    switch (operation)
    {
    /** Digital root in given base **/
    case 1:
        printf("Enter a number and base:\n");
        if (scanf("%d%d", &a, &b) != 2 || a < 0 || b < 0)
        {
            printf("Invalid input: expected two natural numbers. Exiting.\n");
            return 1;
        }
        else if (b < 2)
        {
            printf("Invalid input: base must be greater than 2. Exiting.\n");
            return 1;
        }
        int dr = digital_root_recursive(a, b);
        printf("Digital root of %d in base %d is %d.\n%s",
               a, b, dr,
               (b != 10) && (b < dr) ? "Note, answer is shown in base 10.\n" : "");
        break;
    case 2:
        printf("Enter two numbers:\n");
        if (scanf("%d%d", &a, &b) != 2 || a < 0 || b < 0)
        {
            printf("Invalid input: expected two natural numbers. Exiting.\n");
            return 1;
        }

        printf("Greatest Common Divisor of %d and %d is %d.\n", a, b, gcd_iterative(a, b));
        break;
    case 3:
        printf("Enter two numbers:\n");
        if (scanf("%d%d", &a, &b) != 2 || a < 0 || b < 0)
        {
            printf("Invalid input: expected two natural numbers. Exiting.\n");
            return 1;
        }

        printf("Least common multiple of %d and %d is %d\n", a, b, lcm_iterative(a, b));
        break;
    }
    return 0;
}

int digital_root_recursive(int a, int base)
{
    int s = 0;
    while (a > 0)
    {
        s += a % base;
        a /= base;
    }

    return s < base ? s : digital_root_recursive(s, base);
}

int gcd_iterative(int a, int b)
{
    int t;
    while (b > 0)
    {
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int gcd_recursive(int a, int b)
{
    return a % b == 0 ? b : gcd_recursive(b, a % b);
}

int lcm_iterative(int a, int b)
{
    return a * b / gcd_iterative(a, b);
}

int lcm_recursive(int a, int b)
{
    return a * b / gcd_recursive(a, b);
}
