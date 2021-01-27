/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#ifndef HERAKLIO_GAME_H
#define HERAKLIO_GAME_H

#include <vector>
#include <ncurses.h>

#include "player.h"
#include "bot.h"
#include "game_config.h"
#include "maze.h"
#include "action.h"

namespace Heraklio
{
class Game
{
public:
    Game(GameConfig config);
    ~Game();

    void start();

private:
    void initialize();
    void internal_loop();
    bool handle_actions();
    void handle_bots_actions();
    void mark_visible_around(size_t x, size_t y);
    bool is_visible_at(size_t x, size_t y) const;
    void write_in_header(const char *text);
    void attempt_moving_player_to(Player &player, size_t x, size_t y);
    void attempt_moving_bot_to(Bot &bot, size_t x, size_t y);
    void place_bot_at_random_position(Bot &bot);
    void place_boosts_at_random_positions(size_t count);
    bool collide() const;
    void finish_game(bool won);
    void draw_maze() const;
    void draw_header() const;

    WINDOW *m_window = nullptr;

    const GameConfig m_config;
    Maze m_maze;
    bool *m_visible = nullptr;
    bool m_bots_act_now = false;
    bool m_game_finished = false;
    Player m_player;
    size_t m_player_boost = 0;
    std::vector<Action<Player>> m_actions;

    std::vector<Bot> m_bots;
    std::vector<Action<Bot>> m_bots_actions;
};
}

#endif //HERAKLIO_GAME_H
