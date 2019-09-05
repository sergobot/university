/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "fileUtils.h"
#include <stdio.h>

size_t count_lines_with_words_less_than_or_equal_to(char* filename, size_t n)
{
    FILE *file = fopen(filename, "rt");

    if (file == NULL)
        return 0;

    size_t row_count = 0;
    size_t word_count = 0;
    int c;
    int previous_was_space = 1;

    do
    {
        c = fgetc(file);
        if (c == '\n' || c == EOF)
        {
            if (word_count <= n)
                ++row_count;

            word_count = 0;
            previous_was_space = 1;
        }
        else if (c == ' ')
            previous_was_space = 1;
        else if (previous_was_space == 1)
        {
            ++word_count;
            previous_was_space = 0;
        }
    } while(c != EOF);

    fclose(file);

    return row_count;
}
