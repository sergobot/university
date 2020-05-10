/** Copyright 2018, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include "11.1/digital_root.h"
#include "11.1/gcd_lcm.h"

int main()
{
    printf("Welcome to 11.1! Please choose what to compute (1, 2 or 3):\n"
           "1) Digital root in given base\n"
           "2) Greatest Common Divisor\n"
           "3) Least Common Multiple\n");

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
    /** Greatest Common Divisor **/
    case 2:
        printf("Enter two numbers:\n");
        if (scanf("%d%d", &a, &b) != 2 || a < 0 || b < 0)
        {
            printf("Invalid input: expected two natural numbers. Exiting.\n");
            return 1;
        }

        printf("Greatest Common Divisor of %d and %d is %d.\n", a, b, gcd_iterative(a, b));
        break;
    /** Least Common Multiple **/
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
