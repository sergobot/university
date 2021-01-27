/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#ifndef HERAKLIO_ACTION_H
#define HERAKLIO_ACTION_H

#include <cstdlib>

namespace Heraklio
{
enum ActionType {
    NONE,
    GO_LEFT,
    GO_RIGHT,
    GO_UP,
    GO_DOWN,
    EXIT
};

template<class T>
class Action
{
public:
    Action(ActionType type, T &player) : type(type), player(player) {};

    T &player;
    ActionType type;
};
}

#endif //HERAKLIO_ACTION_H
