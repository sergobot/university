/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <ncurses.h>
#include "colors.h"

namespace Heraklio
{

bool Colors::initialized = false;
void Colors::initialize()
{
    if (!initialized && has_colors())
    {
        start_color();
        init_pair(BLACK_ON_WHITE, COLOR_BLACK, COLOR_WHITE);
        init_pair(WHITE_ON_BLACK, COLOR_WHITE, COLOR_BLACK);
        init_pair(WHITE_ON_GREEN, COLOR_WHITE, COLOR_GREEN);
        init_pair(WHITE_ON_RED, COLOR_WHITE, COLOR_RED);
        init_pair(RED_ON_BLACK, COLOR_RED, COLOR_BLACK);
        init_pair(GREEN_ON_BLACK, COLOR_GREEN, COLOR_BLACK);
        init_pair(BLUE_ON_BLACK, COLOR_BLUE, COLOR_BLACK);
        init_pair(YELLLOW_ON_BLACK, COLOR_YELLOW, COLOR_BLACK);

        initialized = true;
    }
}
}