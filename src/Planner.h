/**
 * @class Planner
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

namespace goap {
    class Planner {
    private:
        std::vector<Node> open_;   // The A* open list
        std::vector<Node> closed_; // The A* closed list

        /**
         Is the given worldstate a member of the closed list? (And by that we mean,
         does any node on the closed list contain an equal worldstate.)
         @param ws the worldstate in question
         @return true if it's been closed, false if not
         */
        bool memberOfClosed(const WorldState& ws) const;

        /**
         Is the given worldstate a member of the open list? (And by that we mean,
         does any node on the open list contain an equal worldstate.)
         @param ws the worldstate in question
         @return a pointer to the note if found, end(open_) if not
         */
        std::vector<goap::Node>::iterator memberOfOpen(const WorldState& ws);

        /**
         Pops the first Node from the 'open' list, moves it to the 'closed' list, and
         returns a reference to this newly-closed Node. Its behavior is undefined if
         you call on an empty list.
         @return a reference to the newly closed Node
         */
        Node& popAndClose();

        /**
         Moves the given Node (an rvalue reference) into the 'open' list.
         @param an rvalue reference to a Node that will be moved to the open list
         */
        void addToOpenList(Node&&);

        /**
         Given two worldstates, calculates an estimated distance (the A* 'heuristic')
         between the two.
         @param now the present worldstate
         @param goal the desired worldstate
         @return an estimated distance between them
         */
        int calculateHeuristic(const WorldState& now, const WorldState& goal) const;

    public:
        Planner();

        /**
         Useful when you're debugging a GOAP plan: simply dumps the open list to stdout.
        */
        void printOpenList() const;

        /**
         Useful when you're debugging a GOAP plan: simply dumps the closed list to stdout.
        */
        void printClosedList() const;

        /**
         Actually attempt to formulate a plan to get from start to goal, given a pool of
         available actions.
         @param start the starting worldstate
         @param goal the goal worldstate
         @param actions the available action pool
         @return a vector of Actions in REVERSE ORDER - use a reverse_iterator on this to get stepwise-order
         @exception std::runtime_error if no plan could be made with the available actions and states
         */
        std::vector<Action> plan(const WorldState& start, const WorldState& goal, const std::vector<Action>& actions);

        TEST_FRIENDS;
    };
}