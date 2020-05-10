/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "count_words.h"

size_t count_words(const char* string)
{
    char last_char = '\0';
    int previous_char_was_space = 0;
    size_t count = 0;

    while (*string != '\0')
    {
        if (*string == ' ')
        {
            if (!previous_char_was_space)
                last_char = *(string - 1);

            previous_char_was_space = 1;
        }
        else
        {
            if (previous_char_was_space && *string == last_char)
                ++count;

            previous_char_was_space = 0;
        }

        ++string;
    }

    return count;
}
