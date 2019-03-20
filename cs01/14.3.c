/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include <stdio.h>
#include <stdlib.h>
#include "14.3/binary_operations.h"
#include "12.1/array_io.h"

int compare_ints(void *_a, void *_b)
{
    int a = *(int *) _a, b = *(int *) _b;
    if (a < b) return -1;
    else if (a == b) return 0;
    else return 1;
}

int main()
{
    printf("Welcome to 14.3! Please enter size of your array of integers:\n");
    int n;
    if (scanf("%d", &n) != 1)
    {
        printf("Invalid input! Exiting.");
        return 1;
    }

    int *a = malloc(n * sizeof(int));
    if (!a)
    {
        printf("Could not allocate memory for your array! Exiting.\n");
        return 2;
    }

    printf("Enter the array of %d elements:\n", n);
    scan_int(a, n);

    printf("Enter the element to look for:\n");
    int e;
    if (scanf("%d", &e) != 1)
    {
        printf("Invalid input! Exiting.");
        free(a);
        return 1;
    }

    void *p = find_in_array(a, &e, n, sizeof(int), compare_ints);
    int pos = find_place_to_put(a, &e, n, sizeof(int), compare_ints);

    if (p != NULL)
        if (pos != -1)
            printf("\nFound it! Element %d can be put at position %d\n", *(int*)p, pos);
        else
        {
            printf("\nInternal error! :( \n");
            free(a);
            return 1;
        }
    else
        printf("%d is %s than all the elements of the array, so put it at position %d\n", e, pos == n ? "larger" : (pos == 0 ? "smaller" : "INTERNAL ERROR"), pos);

    free(a);
    return 0;
}
