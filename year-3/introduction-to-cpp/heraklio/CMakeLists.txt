cmake_minimum_required(VERSION 3.0)
project(pacman)

set(CMAKE_CXX_STANDARD 17)

set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

include_directories(${CURSES_INCLUDE_DIRS})
add_executable(heraklio
        main.cpp
        action.cpp action.h
        maze.cpp maze.h
        random_generator_provider.cpp
        random_generator_provider.h
        game.cpp game.h
        game_config.cpp game_config.h
        player.cpp player.h
        colors.cpp colors.h bot.cpp bot.h)

target_link_libraries(heraklio ${CURSES_LIBRARIES} -pthread)