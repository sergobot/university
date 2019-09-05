/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <stdlib.h>

/**
 * Count lines that have n words or less in a file
 * @param filename - name of the file to go through
 * @param n - number of words
 * @return number of lines.
 */
size_t count_lines_with_words_less_than_or_equal_to(char* filename, size_t n);

#endif // FILEUTILS_H
