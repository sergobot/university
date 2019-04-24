/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "splitString.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char** split_string(const char *string, char *buffer, char** words, const char* delimiters)
{
    size_t length = 0;
    while(*(string + length) != '\0') ++length;

    memcpy(buffer, string, length + 1);

    char *word = strtok(buffer, delimiters);
    int i = 0;
    while (word != NULL)
    {
        words[i++] = word;
        word = strtok(NULL, delimiters);
    }
    words[i] = NULL;

    return words;
}
