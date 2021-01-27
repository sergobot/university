/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#ifndef HERAKLIO_GAME_CONFIG_H
#define HERAKLIO_GAME_CONFIG_H


#include <cstdlib>

namespace Heraklio
{
class GameConfig
{
public:
    static const GameConfig DEFAULT;

    size_t maze_width{}, maze_height{};
    size_t width_multiplier{}, height_multiplayer{};
    size_t player_start_x{}, player_start_y{};
    size_t bots_count{}, bot_range{};
    size_t boosts_count{};

    const wchar_t* player[2] = {L"\u2310\u0CA0\u06FE\u0CA0\u00AC", L" / \\ "};
    const wchar_t* wall[2] = {L"     ", L"     "};
    const wchar_t* empty[2] = {L"     ", L"     "};
    const wchar_t* enemy[2] = {L"\u0295\u25C9\u1D25\u25C9\u0294", L"\u310F \u4E41 "};
    const wchar_t* target[2] = {L"  |\u25B6 ", L"  |  "};
    const wchar_t* boost[2] = {L" \u25E2 \u25E3 ", L" \u25E5 \u25E4 "};
};
}

#endif //HERAKLIO_GAME_CONFIG_H
