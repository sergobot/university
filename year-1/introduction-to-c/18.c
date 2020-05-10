/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <stdlib.h>
#include "18/splitString.h"
#define LENGTH 100

int main()
{
    printf("Welcome to 18.1!\n");

    char a[LENGTH];
    printf("Enter a string:\n");
    if (fgets(a, LENGTH, stdin) == NULL)
    {
        printf("Invalid input :(\nExiting!\n");
        return 1;
    }
    // There may only be no more than ceil(LENGTH / 2) words
    char **words = malloc(LENGTH / 2 + LENGTH % 2), *buffer = malloc(LENGTH);
    split_string_sorted(a, buffer, words, " ,.!?-\n\t");
    
    int i = 0;
    while(*(words + i) != NULL)
    {
        printf("%s\n", *(words + i));
        ++i;
    }

    free(words);
    free(buffer);

    return 0;
}
