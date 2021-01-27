/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include "game_config.h"

namespace Heraklio
{
const GameConfig GameConfig::DEFAULT = {
        .maze_width  = 31,
        .maze_height = 23,
        .width_multiplier = 5,
        .height_multiplayer = 2,
        .player_start_x = 1,
        .player_start_y = 1,
        .bots_count = 5,
        .bot_range = 5,
        .boosts_count = 5
};
}