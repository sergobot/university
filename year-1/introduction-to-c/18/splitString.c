/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "splitString.h"
#include <string.h>

size_t split_string(const char *string, char *buffer, char** words, const char* delimiters)
{
    size_t length = 0;
    while(*(string + length) != '\0') ++length;

    memcpy(buffer, string, length + 1);

    char *word = strtok(buffer, delimiters);
    size_t i = 0;
    while (word != NULL)
    {
        words[i++] = word;
        word = strtok(NULL, delimiters);
    }
    words[i] = NULL;

    return i;
}

size_t split_string_sorted(const char *string, char *buffer, char** words, const char* delimiters)
{
    size_t length = split_string(string, buffer, words, delimiters);

    for (size_t i = 0; i < length-1; i++)
        for (size_t j = 0; j < length-i-1; j++)
        {
            size_t k = 0;
            while(*(*(words + j) + k) == *(*(words + j + 1) + k))
                ++k;
            if ((int)*(*(words + j) + k) > (int)*(*(words + j + 1) + k))
            {
                char *c = words[j];
                words[j] = words[j+1];
                words[j+1] = c;
            }
        }

    return length;
}