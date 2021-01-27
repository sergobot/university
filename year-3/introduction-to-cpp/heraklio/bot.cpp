/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include "random_generator_provider.h"
#include "bot.h"

namespace Heraklio
{

Bot::Bot(size_t range, size_t x /* = 0 */, size_t y /* = 0 */) : m_range(x), m_x(x), m_y(y)
{
}

size_t Bot::get_x() const {
    return m_x;
}

void Bot::set_x(size_t x) {
    m_x = x;
}

size_t Bot::get_y() const {
    return m_y;
}

void Bot::set_y(size_t y) {
    m_y = y;
}

Action<Bot> Bot::act(const Maze &maze, Player &player)
{
    std::deque<std::deque<bool>> visited(maze.get_height(), std::deque<bool>(maze.get_width(), false));

    ActionType type;
    if (!dfs(maze, m_x, m_y, visited, type, 0))
    {
        auto &gen = RandomGeneratorProvider::get();
        std::uniform_int_distribution action_dist((int)GO_LEFT, (int)GO_DOWN);

        type = (ActionType) action_dist(gen);
    }

    return Action<Bot>(type, *this);
}

bool Bot::dfs(const Maze &maze, const size_t x_src, const size_t y_src,
        std::deque<std::deque<bool>> &visited, ActionType &type, size_t step)
{
    if (step >= m_range)
        return false;
    visited[y_src][x_src] = true;
    if (maze.at(x_src, y_src) == Maze::PLAYER)
        type = NONE;
    if (!visited[x_src - 1][y_src] && maze.at(x_src - 1, y_src) != Maze::WALL &&
        dfs(maze, x_src - 1, y_src, visited, type, step + 1))
        type = GO_LEFT;
    else if (!visited[x_src + 1][y_src] && maze.at(x_src + 1, y_src) != Maze::WALL &&
        dfs(maze, x_src + 1, y_src, visited, type, step + 1))
        type = GO_RIGHT;
    else if (!visited[x_src][y_src - 1] && maze.at(x_src, y_src - 1) != Maze::WALL &&
        dfs(maze, x_src, y_src - 1, visited, type, step + 1))
        type = GO_UP;
    else if (!visited[x_src][y_src + 1] && maze.at(x_src, y_src + 1) != Maze::WALL &&
        dfs(maze, x_src, y_src + 1, visited, type, step + 1))
        type = GO_DOWN;
    else
        return false;
    return true;
}


}