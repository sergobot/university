/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <iostream>
#include <iomanip>

#include "random_generator_provider.h"
#include "maze.h"

namespace Heraklio {

Maze::Maze(size_t width, size_t height)
    : m_width(width), m_height(height)
{
    m_maze = new ObjectType[m_width * m_height] {};
    generate();
}

Maze::~Maze()
{
    delete[] m_maze;
}

Maze::ObjectType Maze::at(size_t x, size_t y) const
{
    return m_maze[pos(x, y)];
}

void Maze::set(size_t x, size_t y, ObjectType object)
{
    m_maze[pos(x, y)] = object;
}

size_t Maze::get_width() const
{
    return m_width;
}

size_t Maze::get_height() const
{
    return m_height;
}

void Maze::generate()
{
    for (size_t x = 0; x < m_width; ++x)
    {
        m_maze[pos(x, 0)] = WALL;
        m_maze[pos(x, m_height - 1)] = WALL;
    }
    for (size_t y = 1; y < m_height - 1; ++y)
    {
        m_maze[pos(0, y)] = WALL;
        m_maze[pos(m_width - 1, y)] = WALL;
    }

    generate_recursively(1, 1, m_width - 2, m_height - 2, true);
}

void Maze::generate_recursively(size_t x_start, size_t y_start, size_t x_end, size_t y_end, bool divide_vertically)
{
    if (x_end - x_start <= 1 || y_end - y_start <= 1)
        return;

    std::mt19937 &generator = RandomGeneratorProvider::get();
    size_t x_mid = (x_end + x_start) / 2, y_mid = (y_start + y_end) / 2, opening;

    if (divide_vertically)
    {
        bool already_aligned = (x_mid - x_start) % 2;
        int move = already_aligned ? 0 : std::uniform_int_distribution(0, 1)(generator) ? 1 : -1;
        x_mid += move;

        bool start_clear = at(x_mid, y_start - 1) == EMPTY, end_clear = at(x_mid, y_end + 1) == EMPTY;
        // Check if the new wall will block an existing passage
        if(start_clear && !end_clear)
            opening = y_start;
        else if(!start_clear && end_clear)
            opening = y_end;
        else
        {
            if (start_clear && end_clear)
                x_mid -= 2 * move;
            std::uniform_int_distribution opening_dist(y_start, y_end);
            while ((opening = opening_dist(generator)) == y_mid);
        }

        for (size_t y = y_start; y <= y_end; ++y)
            if (y != opening)
                m_maze[pos(x_mid, y)] = WALL;

        generate_recursively(x_start, y_start, x_mid - 1, y_end, false);
        generate_recursively(x_mid + 1, y_start, x_end, y_end, false);
    }
    else
    {
        bool already_aligned = (y_mid - y_start) % 2;
        int move = already_aligned ? 0 : std::uniform_int_distribution(0, 1)(generator) ? 1 : -1;
        y_mid += move;

        bool start_clear = at(x_start - 1, y_mid) == EMPTY, end_clear = at(x_end + 1, y_mid) == EMPTY;
        // Check if the new wall will block an existing passage
        if(start_clear && !end_clear)
            opening = x_start;
        else if(!start_clear && end_clear)
            opening = x_end;
        else
        {
            if (start_clear && end_clear)
                y_mid -= 2 * move;
            std::uniform_int_distribution opening_dist(x_start, x_end);
            while ((opening = opening_dist(generator)) == x_mid);
        }

        for (size_t x = x_start; x <= x_end; ++x)
            if (x != opening)
                m_maze[pos(x, y_mid)] = WALL;

        generate_recursively(x_start, y_start, x_end, y_mid - 1, true);
        generate_recursively(x_start, y_mid + 1, x_end, y_end, true);
    }
}

inline size_t Maze::pos(size_t x, size_t y) const
{
    return x + m_width * y;
}

}