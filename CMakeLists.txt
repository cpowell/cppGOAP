#cmake_minimum_required(VERSION 3.12)
#project(GOAP)
#
#set(CMAKE_CXX_STANDARD 14)
#
#include_directories(goap)
#include_directories(wargame_example)
#include_directories(weapon_example)
#
#add_executable(GOAP
#        goap/Action.cpp
#        goap/Action.h
#        goap/Node.cpp
#        goap/Node.h
#        goap/Planner.cpp
#        goap/Planner.h
#        goap/WorldState.cpp
#        goap/WorldState.h
#        goap_tests/ActionTest.cpp
#        goap_tests/NodeTest.cpp
#        goap_tests/PlannerTest.cpp
#        goap_tests/WorldStateTest.cpp
#        wargame_example/main.cpp
#        weapon_example/main.cpp)

cmake_minimum_required(VERSION 3.12)
project(GOAP)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory (goap)
add_subdirectory (wargame_example)
add_subdirectory (weapon_example)
