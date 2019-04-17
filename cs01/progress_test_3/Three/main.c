#include <stdio.h>
#include <stdlib.h>

#include "find_kth_word.h"
#define LENGTH 100

int main()
{
    printf("Welcome to Three! Please enter your string:\n");

    char a[LENGTH];
    if (fgets(a, LENGTH, stdin) == NULL)
    {
        printf("Invalid input :(\nExiting!\n");
        return 1;
    }

    printf("Now please enter k:\n");

    int k;
    if (scanf("%d", &k) != 1)
    {
        printf("Invalid input :(\nExiting!\n");
        return 1;
    }

    printf("The string starting from k-th word:\n%s", find_kth_word(a, k));

    return 0;
}
