/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "fileUtils.h"

size_t count_lines_with_last_symbol(const char *filename, char symbol)
{
    FILE *file = fopen(filename, "r");

    if (file == NULL)
        return 0;

    size_t count = 0;
    char previous = '\0';
    int c;
    while ((c = fgetc(file)) != EOF)
    {
        if (c == '\n' && previous == symbol)
            ++count;

        previous = c;
    }
    if (previous == symbol)
        ++count;

    fclose(file);

    return count;
}
