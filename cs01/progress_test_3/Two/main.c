/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <stdlib.h>

#include "find_smallest.h"

int main()
{
    printf("Welcome to Two! Please enter size of your array:\n");

    int length;
    if (scanf("%d", &length) != 1)
    {
        printf("Invalid input :(\nExiting!\n");
        return 1;
    }

    long *a = malloc(length * sizeof(long));
    long *end = a + length;

    long *iterator = a;

    printf("Now, enter your array:\n");
    while(iterator != end)
    {
        if (scanf("%ld", iterator) != 1)
        {
            printf("Invalid input :(\nExiting!\n");
            return 1;
        }
        ++iterator;
    }

    printf("The smallest number is %ld\n", (long)(*find_smallest(a, length)));

    free(a);
    return 0;
}
