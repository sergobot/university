/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef SPLITSTRING_H
#define SPLITSTRING_H

/**
 * Sum all the number's digits in numeral system with arbitrary base.
 * @param string - the string to split.
 * @param delimiters - string of characters to split `string` by.
 * @return pointer to an array of pointers to start of each word.
 */
char** split_string(const char* string, char *buffer, char** words, const char* delimiters);

#endif // SPLITSTRING_H
