/* Copyright 2020, Sergey Popov (me@sergobot.me) */

#include <thread>
#include <chrono>
#include <locale>
#include <cwchar>
#include <random>
#include <cstring>
#include <algorithm>

#include "colors.h"
#include "game.h"
#include "random_generator_provider.h"

namespace Heraklio
{

Game::Game(GameConfig config)
    : m_config(config)
    , m_maze(config.maze_width, config.maze_height)
    , m_player(config.player_start_x, config.player_start_y)
{
    initialize();
}

Game::~Game()
{
    delete[] m_visible;

    wborder(m_window, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    wrefresh(m_window);
    delwin(m_window);

    endwin();
}

void Game::initialize()
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    Colors::initialize();

    size_t window_height = m_config.maze_height * m_config.height_multiplayer + 4;
    size_t window_width = m_config.maze_width * m_config.width_multiplier + 2;
    size_t window_start_x = (COLS - window_width) / 2;
    size_t window_start_y = (LINES - window_height) / 2;

    m_window = newwin(window_height, window_width, window_start_y, window_start_x);
    wtimeout(m_window, 0);
    box(m_window, 0, 0);
    wrefresh(m_window);

    m_player.set_x(m_config.player_start_x);
    m_player.set_y(m_config.player_start_y);
    m_maze.set(m_config.player_start_x,  m_config.player_start_y, Maze::PLAYER);

    m_visible = new bool[m_config.maze_width * m_config.maze_height] {};
    mark_visible_around(m_player.get_x(), m_player.get_y());

    for (size_t i = 0; i < m_config.bots_count; ++i)
        m_bots.emplace_back(m_config.bot_range);
    for (auto &bot : m_bots)
        place_bot_at_random_position(bot);

    place_boosts_at_random_positions(m_config.boosts_count);

    m_maze.set(m_config.maze_width - 2, m_config.maze_height - 2, Maze::TARGET);
}

void Game::start()
{
    internal_loop();
}

void Game::internal_loop()
{
    auto timer = []() { std::this_thread::sleep_for(std::chrono::milliseconds(100));};
    bool exit = false;
    size_t i = 0;

    while (!exit)
    {
        std::thread timer_thread(timer);

        draw_maze();
        draw_header();

        m_actions.push_back(m_player.get_pending_action(m_window));
        exit = handle_actions();

        if (m_bots_act_now)
        {
            for (Bot &bot : m_bots)
                m_bots_actions.push_back(bot.act(m_maze, m_player));
            handle_bots_actions();
        }

        if (m_player_boost > 0) --m_player_boost;
        m_bots_act_now = !m_bots_act_now;

        timer_thread.join();
    }
}

void Game::draw_maze() const
{
    for (size_t i = 0; i < m_maze.get_height(); ++i)
    {
        for (size_t j = 0; j < m_maze.get_width(); ++j)
        {
            const wchar_t* row_1;
            const wchar_t* row_2;
            int color_pair;

            if (/*is_visible_at(j, i)*/ true)
            {
                switch (m_maze.at(j, i))
                {
                    wattron(m_window, A_BOLD);
                    case Maze::WALL:
                        row_1 = m_config.wall[0];
                        row_2 = m_config.wall[1];
                        color_pair = COLOR_PAIR(Colors::BLACK_ON_WHITE);
                        break;
                    case Maze::EMPTY:
                        row_1 = m_config.empty[0];
                        row_2 = m_config.empty[1];
                        color_pair = COLOR_PAIR(Colors::WHITE_ON_BLACK);
                        break;
                    case Maze::PLAYER:
                        row_1 = m_config.player[0];
                        row_2 = m_config.player[1];
                        color_pair = COLOR_PAIR(Colors::YELLLOW_ON_BLACK);
                        break;
                    case Maze::TARGET:
                        row_1 = m_config.target[0];
                        row_2 = m_config.target[1];
                        color_pair = COLOR_PAIR(Colors::WHITE_ON_GREEN);
                        break;
                    case Maze::ENEMY:
                        row_1 = m_config.enemy[0];
                        row_2 = m_config.enemy[1];
                        color_pair = COLOR_PAIR(Colors::RED_ON_BLACK);
                        break;
                    case Maze::BOOST:
                        row_1 = m_config.boost[0];
                        row_2 = m_config.boost[1];
                        color_pair = COLOR_PAIR(Colors::BLUE_ON_BLACK);
                        break;
                    default:
                        break;
                }
            }
            else
            {
                row_1 = m_config.empty[0];
                row_2 = m_config.empty[1];
                color_pair = COLOR_PAIR(Colors::WHITE_ON_BLACK);
            }

            wattron(m_window, color_pair);
            mvwaddwstr(m_window, m_config.height_multiplayer*i + 3, j * m_config.width_multiplier + 1, row_1);
            mvwaddwstr(m_window, m_config.height_multiplayer*i + 4, j * m_config.width_multiplier + 1, row_2);
            wattroff(m_window, color_pair);
            wattroff(m_window, A_BOLD);
        }
    }
}

void Game::draw_header() const
{
    wattron(m_window, A_BOLD);
    wattron(m_window, Colors::BLUE_ON_BLACK);
    mvwprintw(m_window, 1, 1, "BOOST: %d", m_player_boost);
    wattroff(m_window, Colors::BLUE_ON_BLACK);
    wattroff(m_window, A_BOLD);
}

void Game::attempt_moving_player_to(Player &player, size_t x, size_t y)
{
    switch(m_maze.at(x, y))
    {
        case Maze::PLAYER:
        case Maze::WALL:
            return;
        case Maze::EMPTY:
            m_maze.set(x, y, Maze::PLAYER);
            m_maze.set(player.get_x(), player.get_y(), Maze::EMPTY);
            player.set_x(x);
            player.set_y(y);
            mark_visible_around(x, y);
            break;
        case Maze::ENEMY:
            if (collide())
            {
                for (size_t i = 0; i < m_bots.size(); ++i)
                    if (m_bots.at(i).get_x() == x && m_bots.at(i).get_y() == y)
                    {
                        m_bots.erase(m_bots.begin() + i);
                        break;
                    }
                m_maze.set(x, y, Maze::PLAYER);
                m_maze.set(player.get_x(), player.get_y(), Maze::EMPTY);
                player.set_x(x);
                player.set_y(y);
                mark_visible_around(x, y);
            }
            else
            {
                finish_game(false);
            }
            break;
        case Maze::TARGET:
            m_maze.set(player.get_x(), player.get_y(), Maze::EMPTY);
            player.set_x(x);
            player.set_y(y);
            mark_visible_around(x, y);
            finish_game(true);
            break;
        case Maze::BOOST:
            m_maze.set(player.get_x(), player.get_y(), Maze::EMPTY);
            m_maze.set(x, y, Maze::PLAYER);
            player.set_x(x);
            player.set_y(y);
            m_player_boost += 100;
            mark_visible_around(x, y);
            break;
    }
}

void Game::mark_visible_around(size_t x, size_t y)
{
    for (size_t i = std::max((int)x - 2, 0); i <= std::min(x + 2, m_config.maze_width - 1); ++i)
        for (size_t j = std::max((int)y - 2, 0); j <= std::min(y + 2, m_config.maze_height - 1); ++j)
            m_visible[i * m_config.maze_height + j] = true;
}

bool Game::is_visible_at(size_t x, size_t y) const
{
    return m_visible[x * m_config.maze_height + y];
}

void Game::write_in_header(const char *text)
{
    mvwprintw(m_window, 1, (m_config.maze_width * m_config.width_multiplier - strlen(text)) / 2,  "%s", text);
}

bool Game::collide() const
{
    return m_player_boost > 0;
}

void Game::attempt_moving_bot_to(Bot &bot, size_t x, size_t y)
{
    switch(m_maze.at(x, y))
    {
        case Maze::BOOST:
        case Maze::EMPTY:
            m_maze.set(bot.get_x(), bot.get_y(), Maze::EMPTY);
            m_maze.set(x, y, Maze::ENEMY);
            bot.set_x(x);
            bot.set_y(y);
            break;
        case Maze::PLAYER:
            if (collide())
            {
                for (size_t i = 0; i < m_bots.size(); ++i)
                    if (m_bots.at(i).get_x() == bot.get_x() && m_bots.at(i).get_y() == bot.get_y())
                    {
                        m_bots.erase(m_bots.begin() + i);
                        break;
                    }
            }
            else
            {
                m_maze.set(bot.get_x(), bot.get_y(), Maze::EMPTY);
                m_maze.set(x, y, Maze::ENEMY);
                bot.set_x(x);
                bot.set_y(y);
                finish_game(false);
            }

            break;
        case Maze::ENEMY:
        case Maze::WALL:
        case Maze::TARGET:
            return;
    }
}

void Game::place_bot_at_random_position(Bot &bot)
{
    std::uniform_int_distribution x_dist(0, (int)m_config.maze_width);
    std::uniform_int_distribution y_dist(0, (int)m_config.maze_height);
    auto &gen = RandomGeneratorProvider::get();

    size_t x, y;
    while(m_maze.at(x = x_dist(gen), y = y_dist(gen)) != Maze::EMPTY);

    m_maze.set(x, y, Maze::ENEMY);
    bot.set_x(x);
    bot.set_y(y);
}

void Game::place_boosts_at_random_positions(size_t count)
{
    std::uniform_int_distribution x_dist(0, (int)m_config.maze_width);
    std::uniform_int_distribution y_dist(0, (int)m_config.maze_height);
    auto &gen = RandomGeneratorProvider::get();

    size_t x, y;
    for (size_t i = 0; i < count; ++i)
    {
        while(m_maze.at(x = x_dist(gen), y = y_dist(gen)) != Maze::EMPTY);
        m_maze.set(x, y, Maze::BOOST);
    }
}

void Game::finish_game(bool won)
{
    m_game_finished = true;
    if (won)
    {
        write_in_header("You won the game! Press 'q' to exit.");
    }
    else
    {
        write_in_header("Don't be too disappointed, but you died :( Press 'q' to exit.");
    }
}

bool Game::handle_actions()
{
    for (const auto &action : m_actions)
    {
        if (m_game_finished && action.type != ActionType::EXIT)
            continue;

        size_t x = action.player.get_x(), y = action.player.get_y();
        switch(action.type)
        {
            case ActionType::GO_LEFT:
                attempt_moving_player_to(action.player, x - 1, y);
                break;
            case ActionType::GO_RIGHT:
                attempt_moving_player_to(action.player, x + 1, y);
                break;
            case ActionType::GO_UP:
                attempt_moving_player_to(action.player, x, y - 1);
                break;
            case ActionType::GO_DOWN:
                attempt_moving_player_to(action.player, x, y + 1);
                break;
            case ActionType::EXIT:
                return true;
            case ActionType::NONE:
                break;
        }
    }
    m_actions.clear();
    return false;
}

void Game::handle_bots_actions()
{
    for (const auto &action : m_bots_actions)
    {
        size_t x = action.player.get_x(), y = action.player.get_y();
        switch (action.type)
        {
            case GO_LEFT:
                attempt_moving_bot_to(action.player, x - 1, y);
                break;
            case GO_RIGHT:
                attempt_moving_bot_to(action.player, x + 1, y);
                break;
            case GO_UP:
                attempt_moving_bot_to(action.player, x, y - 1);
                break;
            case GO_DOWN:
                attempt_moving_bot_to(action.player, x, y + 1);
                break;
            case EXIT:
                return;
            case NONE:
                break;
        }
    }
    m_bots_actions.clear();
}

}