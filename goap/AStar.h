/**
 * @class AStar
 * @brief Implements an A* algorithm for searching the action space
 *
 * @date July 2014
 * @copyright (c) 2014 Prylis Inc. All rights reserved.
 */

#pragma once

#include "Action.h"
#include "Node.h"
#include "WorldState.h"

#include <ostream>
#include <vector>

// To support Google Test for private members
#ifndef TEST_FRIENDS
#define TEST_FRIENDS
#endif

class AStar {
private:
    WorldState start_;
    WorldState goal_;

    std::vector<Node> open_;
    std::vector<Node> closed_;

    int calculateHeuristic(const WorldState& now, const WorldState& goal) const;
    void addToOpenList(Node&&);
    Node& popAndClose();
    bool memberOfClosed(const WorldState& ws) const;
    bool memberOfOpen(const WorldState& ws) const;

public:
    AStar();

    void setStart(WorldState w) { start_ = w; }
    void setGoal(WorldState w) { goal_ = w; }

    void printOpenList() const;
    void printClosedList() const;

    //int astar_plan(
    //    ActionPlanner *ap,       //!< the goap action planner that holds atoms and action repertoire
    //    WorldState start,        //!< the current world state
    //    WorldState goal,         //!< the desired world state
    //    const char **plan,       //!< for returning all actions that make up plan
    //    WorldState *worldstates, //!< for returning intermediate world states
    //    int *plansize            //!< in: size of plan buffer, out: size of plan (in nr of steps)
    //    );

    void plan(std::vector<Action>& actions);

    TEST_FRIENDS;
};

