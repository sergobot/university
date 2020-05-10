/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "find_kth_word.h"

const char *find_kth_word(const char *string, size_t k)
{
    int previous_char_was_space = 1;

    while (*string != '\0')
    {
        if (*string == ' ')
            previous_char_was_space = 1;
        else
        {
            if (previous_char_was_space && k-- == 0)
            {
                return string;
            }
            previous_char_was_space = 0;
        }
        ++string;
    }

    return NULL;
}
