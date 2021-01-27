/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#ifndef HERAKLIO_COLORS_H
#define HERAKLIO_COLORS_H

namespace Heraklio
{
class Colors
{
public:
    enum COLOR_PAIR
    {
        BLACK_ON_WHITE = 1,
        WHITE_ON_BLACK,
        WHITE_ON_GREEN,
        WHITE_ON_RED,
        RED_ON_BLACK,
        GREEN_ON_BLACK,
        BLUE_ON_BLACK,
        YELLLOW_ON_BLACK
    };

    static void initialize();

private:
    static bool initialized;
};
}


#endif //HERAKLIO_COLORS_H
