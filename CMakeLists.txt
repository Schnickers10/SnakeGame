cmake_minimum_required(VERSION 3.15)
project(SnakeGame CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib CONFIG REQUIRED)

add_executable(SnakeGame main.cpp)
target_link_libraries(SnakeGame PRIVATE raylib)
