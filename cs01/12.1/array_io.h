/** Copyright 2018-2019, Sergey Popov (me@sergobot.me) **/

#ifndef ARRAY_IO_H
#define ARRAY_IO_H

/** Scans an array of n elements of int from stdin **/
int scan_int(int *arr, size_t n);

/** Scans an array of n elements of double from stdin **/
int scan_double(double *arr, size_t n);

/** Prints an array of n elements of type int **/
void print_int(int *arr, size_t n);

/** Prints an array of n elements of type double **/
void print_double(double *arr, size_t n);

#endif // ARRAY_IO_H
