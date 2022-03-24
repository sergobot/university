cmake_minimum_required(VERSION 3.0)
project(graphics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(SOURCES
        main.cpp my_canvas.cpp my_canvas.h)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(graphics ${SOURCES} graphics.qrc)
target_link_libraries(graphics Qt5::Widgets)
