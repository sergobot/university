/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <stdlib.h>

size_t trim_spaces(char *a);

char* substring(const char *src, char *dst, long start, long new_length);

void change_first_and_last_letter(char *a);

#endif // STRINGUTILS_H
