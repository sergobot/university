/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "stringUtils.h"
#include <string.h>

size_t trim_spaces(char *a)
{
    char *reading = a, *writing = a;
    size_t pos = 0;

    while (*reading == ' ')
        ++reading;

    int previous_char_was_space = 0;
    while (*reading != '\0')
    {
        if (*reading == ' ')
            previous_char_was_space = 1;
        else
        {
            if (previous_char_was_space)
            {
                *writing = ' ';
                ++writing;
                previous_char_was_space = 0;
                ++pos;
            }
            *writing = *reading;
            ++writing;
            ++pos;
        }
        ++reading;
    }
    *writing = '\0';
    return pos;
}

long max(long a, long b)
{
    return a > b ? a : b;
}

long min(long a, long b)
{
    return a < b ? a : b;
}

char* substring(const char *src, char* dst, long start, long new_length)
{
    long length = 0;
    while (*(src + length) != '\0')
        ++length;

    if (start < 0)
        start = max(length + start, 0);

    if ((start >= length && start + new_length >= length) || (start == 0 && new_length <= 0))
    {
        dst = "";
        return dst;
    }

    long end = min(length, max(start, min(start + new_length, length)));
    start = max(0, min(start + new_length, start));

    if (start < 0 || end < 0)
    {
        dst = "";
        return dst;
    }

    new_length = end - start;

    memcpy(dst, src + start, new_length + 1);
    dst[new_length] = '\0';

    return dst;
}

void change_first_and_last_letter(char *a)
{
    char *first_char_of_the_word = NULL;
    int previous_char_was_space = 1;
    while (*a != '\0')
    {
        if (*a == ' ' || *a == '\n')
        {
            if (!previous_char_was_space && first_char_of_the_word != NULL)
            {
                char c = *first_char_of_the_word;
                *first_char_of_the_word = *(a - 1);
                *(a - 1) = c;
            }
            previous_char_was_space = 1;
        }
        else
        {
            if (previous_char_was_space)
            {
                first_char_of_the_word = a;
            }
            previous_char_was_space = 0;
        }

        ++a;
    }

    if (!previous_char_was_space && first_char_of_the_word != NULL)
    {
        // Replace chars of the last word
        char c = *first_char_of_the_word;
        *first_char_of_the_word = *(a - 1);
        *(a - 1) = c;
    }
}
