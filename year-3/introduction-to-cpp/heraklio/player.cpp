/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include "player.h"

namespace Heraklio
{
Player::Player(size_t x, size_t y) : m_x(x), m_y(y)
{
}

size_t Player::get_x() const
{
    return m_x;
}

size_t Player::get_y() const
{
    return m_y;
}

void Player::set_x(size_t x)
{
    m_x = x;
}

void Player::set_y(size_t y)
{
    m_y = y;
}
Action<Player> Player::get_pending_action(WINDOW *window)
{
    int user_input, temp;
    while ((temp = wgetch(window)) != ERR)
    {
        user_input = temp;
    }

    ActionType type;
    switch (user_input)
    {
        case 'q':
        case 'Q':
            type = ActionType::EXIT;
            break;
        case 'a':
        case 'A':
            type = ActionType::GO_LEFT;
            break;
        case 'd':
        case 'D':
            type = ActionType::GO_RIGHT;
            break;
        case 'w':
        case 'W':
            type = ActionType::GO_UP;
            break;
        case 's':
        case 'S':
            type = ActionType::GO_DOWN;
            break;
        default:
            type = ActionType::NONE;
    }
    wrefresh(window);

    return Action(type, *this);
}

}
