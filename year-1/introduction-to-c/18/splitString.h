/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef SPLITSTRING_H
#define SPLITSTRING_H

#include <stdlib.h>

/**
 * Split a string with regards to delimiters, put it into buffer and save pointers to words in words.
 * @param string - the string to split.
 * @param delimiters - string of characters to split `string` by.
 * @return number of words.
 */
size_t split_string(const char* string, char *buffer, char** words, const char* delimiters);

/**
 * Split a string with regards to delimiters, put it into buffer, sort the words and save pointers to them in words.
 * @param string - the string to split.
 * @param delimiters - string of characters to split `string` by.
 * @return number of words.
 */
size_t split_string_sorted(const char* string, char *buffer, char** words, const char* delimiters);

#endif // SPLITSTRING_H
