/** Copyright 2019, Sergey Popov (me@sergobot.me) **/

#include "longest_vector.h"
#include <math.h>

double find_longest_vector_in_file(FILE* file)
{
    if (file == NULL)
    {
        return -1;
    }

    double max_length = -1;
    double length = 0;
    int c = 0;
    while(c != EOF)
    {
        double number;
        fscanf(file, "%lf", &number);
        length += number * number;
        c = fgetc(file);
        if (c == EOF || c == '\n')
        {
            length = sqrt(length);
            if (max_length < length)
                max_length = length;

            length = 0;
        }
    }

    return max_length;
}
