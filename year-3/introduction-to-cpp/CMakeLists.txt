cmake_minimum_required(VERSION 3.0)
project(introduction-to-cpp)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)

add_executable(task-1 task-1.cpp)
add_executable(task-2 task-2.cpp)
add_executable(task-3 task-3.cpp task-3.h)
add_executable(task-4 task-4.cpp)
add_executable(task-5 task-5.cpp)
add_executable(task-6 task-6.cpp)
add_executable(task-7 task-7.cpp)
add_executable(string string/string.cpp)
add_executable(shapes shapes/shape.h shapes/main.cpp shapes/rectangle.cpp shapes/rectangle.h shapes/circle.cpp shapes/circle.h shapes/shape.cpp)

add_subdirectory(graphics)