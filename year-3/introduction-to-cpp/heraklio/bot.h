/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#ifndef HERAKLIO_BOT_H
#define HERAKLIO_BOT_H

#include <cstdlib>
#include <deque>
#include <vector>

#include "action.h"
#include "player.h"
#include "maze.h"

namespace Heraklio
{
class Bot
{
public:
    Bot(size_t range, size_t x = 0, size_t y = 0);

    Action<Bot> act(const Maze &maze, Player &player);

    [[nodiscard]] size_t get_x() const;
    [[nodiscard]] size_t get_y() const;

    void set_x(size_t x);
    void set_y(size_t y);
private:
    size_t m_range, m_x, m_y;

    bool dfs(const Maze &maze, const size_t x_src, const size_t y_src,
            std::deque<std::deque<bool>> &visited, ActionType &type, size_t step);
};
}

#endif //HERAKLIO_BOT_H
