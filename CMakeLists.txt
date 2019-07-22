cmake_minimum_required(VERSION 3.12)
project(GOAP)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(src)
add_subdirectory(examples/wargame_example EXCLUDE_FROM_ALL)
add_subdirectory(examples/assassin_example EXCLUDE_FROM_ALL)
