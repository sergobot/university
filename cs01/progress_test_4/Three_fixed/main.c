/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <stdlib.h>

#include "fileUtils.h"

int main()
{
    printf("Welcome to Three! What file do you want me to read from?\n");

    char filename[FILENAME_MAX];
    if (scanf("%s", filename) != 1)
    {
        printf("Invalid input :(\nExiting!\n");
        return 1;
    }

    printf("All right! Will be reading from %s\n", filename);

    printf("What should be the number of words?\n");

    size_t n;
    if (scanf("%ld", (long*)&n) != 1)
    {
        printf("Invalid input :(\nExiting!\n");
        return 1;
    }

    printf("There are %ld lines with %ld words or less.\n",
           (long)count_lines_with_words_less_than_or_equal_to(filename, n), (long)n);

    return 0;
}
