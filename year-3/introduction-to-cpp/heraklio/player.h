/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#ifndef HERAKLIO_PLAYER_H
#define HERAKLIO_PLAYER_H

#include <ncurses.h>
#include "action.h"

namespace Heraklio
{
class Player
{
public:
    Player(size_t x, size_t y);

    Action<Player> get_pending_action(WINDOW *window);

    [[nodiscard]] size_t get_x() const;
    [[nodiscard]] size_t get_y() const;

    void set_x(size_t x);
    void set_y(size_t y);

private:
    size_t m_x, m_y;
};
}

#endif //HERAKLIO_PLAYER_H
