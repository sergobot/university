/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#ifndef BINARY_SEARCH_H
#define BINARY_SEARCH_H

// Should return -1 if a < b, 0 if a = b, 1 if a > b.
typedef int (*compare) (void *a, void *b);

void* find_in_array(void *a, void *e, int length, int size, compare f);

int find_place_to_put(void *a, void *e, int length, int size, compare f);

#endif // BINARY_SEARCH_H
