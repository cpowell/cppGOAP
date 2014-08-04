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
#include <unordered_map>
#include <vector>

// To support Google Test for private members
#ifndef TEST_FRIENDS
#define TEST_FRIENDS
#endif

class AStar {
private:
    WorldState start_;
    WorldState goal_;

    std::unordered_map<int, Node> known_nodes_;
    std::vector<Node> open_;
    std::vector<Node> closed_;

    bool memberOfClosed(const WorldState& ws) const;

    Node* memberOfOpen(const WorldState& ws);

    /**
     Pops the first Node from the 'open' list, moves it to the 'closed' list, and
     returns a reference to this newly-closed Node.
     @return a reference to the newly closed Node
     @exception std::invalid_argument if the 'open' list has zero elements
    */
    Node& popAndClose();

    /**
     Moves the given Node (an rvalue reference) into the 'open' list.
     @param an rvalue reference to a Node
    */
    void addToOpenList(Node&&);

    int calculateHeuristic(const WorldState& now, const WorldState& goal) const;

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

