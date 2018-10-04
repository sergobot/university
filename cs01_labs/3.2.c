/* Copyright 2018, Sergey Popov (me@sergobot.me) */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int seconds;
    printf("Enter the number of seconds:\n");
    if (scanf("%d", &seconds) != 1)
    {
        printf("Ambiguous input. Exiting.\n");
        return 1;
    }

    int sec = seconds % 60;
    seconds /= 60;
    int min = seconds % 60;
    printf("The time is %02d:%02d\n", min, sec);

    return 0;
}
