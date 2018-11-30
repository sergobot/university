/** Copyright 2018, Sergey Popov (me@sergobot.me) **/

#include "digital_root.h"

/** Compute digital root of a in base base **/
int digital_root_recursive(int a, int base)
{
    int s = 0;
    while (a > 0)
    {
        s += a % base;
        a /= base;
    }

    return s < base ? s : digital_root_recursive(s, base);
}
