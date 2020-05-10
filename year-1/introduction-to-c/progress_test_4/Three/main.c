/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <stdlib.h>

#include "fileUtils.h"

int main()
{
    printf("Welcome to Three! I will be reading from input.txt. Please enter your symbol:\n");

    char c;
    if (scanf("%c", &c) != 1)
    {
        printf("Invalid input :(\nExiting!\n");
        return 1;
    }

    const char* filename = "input.txt";

    printf("There are %d lines with '%c' in the end\n", (int)count_lines_with_last_symbol(filename, c), c);

    return 0;
}
