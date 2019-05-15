/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "fileUtils.h"

size_t count_lines_with_last_symbol(FILE *file, char symbol)
{
    if (file == NULL)
        return 0;

    size_t count = 0;
    char previous = '\0';
    char c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n' && previous == symbol)
            ++count;

        previous = c;
    }

    return count;
}
