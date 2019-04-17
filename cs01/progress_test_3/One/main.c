/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <stdlib.h>

#include "count_words.h"
#define LENGTH 100

int main()
{
    printf("Welcome to One! Please enter your string:\n");

    char a[LENGTH];
    if (fgets(a, LENGTH, stdin) == NULL)
    {
        printf("Invalid input :(\nExiting!\n");
        return 1;
    }

    printf("There are %d such words\n", (int)count_words(a));

    return 0;
}
