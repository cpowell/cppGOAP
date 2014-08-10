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

namespace goap {
    class AStar {
    private:
        WorldState start_; // where we begin
        WorldState goal_;  // where we want to end up

        // A master lookup table of ID-to-Node; useful during the action replay
        std::unordered_map<int, Node> known_nodes_;

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
         @return a pointer to the note if found, nullptr if not
         */
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
        AStar();

        void setStart(WorldState w) { start_ = w; }
        void setGoal(WorldState w) { goal_ = w; }

        void printOpenList() const;
        void printClosedList() const;

        /**
         Actually attempt to formulate a plan from start to goal, given a pool of
         available actions.
         @param actions the available action pool
         */
        void plan(std::vector<Action>& actions);

        TEST_FRIENDS;
    };
}