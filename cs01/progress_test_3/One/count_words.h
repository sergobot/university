/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef COUNT_WORDS_H
#define COUNT_WORDS_H

#include <stdlib.h>

/**
 * Count words that start with the same letter as the previous word ends with.
 * @param string - array of chars to count words in.
 * @return number of specific words.
 */
size_t count_words(const char *string);

#endif // COUNT_WORDS_H
