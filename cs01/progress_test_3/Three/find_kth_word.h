/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef FIND_KTH_WORD_H
#define FIND_KTH_WORD_H

#include <stdlib.h>

/**
 * Returns pointer to the k-th word (starting from 0) in the string.
 * @param string - array of chars to find the word in.
 * @param k - number of the word to return.
 * @return pointer to the start of that word.
 */
const char *find_kth_word(const char *string, size_t k);

#endif // FIND_KTH_WORD_H
