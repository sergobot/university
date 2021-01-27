/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#ifndef HERAKLIO_MAZE_H
#define HERAKLIO_MAZE_H

#include <cstdlib>

namespace Heraklio
{

class Maze
{
public:
    enum ObjectType
    {
        EMPTY,
        WALL,
        PLAYER,
        ENEMY,
        TARGET,
        BOOST
    };

    Maze(size_t width, size_t height);
    ~Maze();

    [[nodiscard]] ObjectType at(size_t x, size_t y) const;
    void set(size_t x, size_t y, ObjectType object);

    [[nodiscard]] size_t get_width() const;

    [[nodiscard]] size_t get_height() const;

private:
    void generate();
    void generate_recursively(size_t x_start, size_t y_start, size_t x_end, size_t y_end, bool divide_vertically);

    [[nodiscard]] inline size_t pos(size_t x, size_t y) const;

    size_t m_width, m_height;
    ObjectType *m_maze = nullptr;
};

}

#endif //HERAKLIO_MAZE_H
