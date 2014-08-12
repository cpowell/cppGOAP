#include "AStar.h"

#include <algorithm>
#include <iostream>

goap::AStar::AStar() {
}

int goap::AStar::calculateHeuristic(const WorldState& now, const WorldState& goal) const {
    return now.distanceTo(goal);
}

void goap::AStar::addToOpenList(Node&& n) {
    // insert maintaining sort order
    auto it = std::lower_bound(begin(open_),
                               end(open_),
                               n);
    open_.emplace(it, std::move(n));
}

goap::Node& goap::AStar::popAndClose() {
    if (open_.size() == 0) {
        throw std::invalid_argument("You cannot call popAndClose on an empty open-list!");
    }

    closed_.push_back(std::move(open_.front()));
    open_.erase(open_.begin());

    return closed_.back();
}

bool goap::AStar::memberOfClosed(const WorldState& ws) const {
    if (std::find_if(begin(closed_), end(closed_), [&](const Node& n) { return n.ws_ == ws; }) == end(closed_)) {
        return false;
    } else {
            return true;
        }
    }

std::vector<goap::Node>::iterator goap::AStar::memberOfOpen(const WorldState& ws) {
    return std::find_if(begin(open_), end(open_), [&](const Node& n) { return n.ws_ == ws; });
}

void goap::AStar::printOpenList() const {
    for (const auto& n : open_) {
        std::cout << n << std::endl;
    }
}

void goap::AStar::printClosedList() const {
    for (const auto& n : closed_) {
        std::cout << n << std::endl;
    }
}

std::vector<goap::Action> goap::AStar::plan(const WorldState& start, const WorldState& goal, const std::vector<Action>& actions) {
    // Feasible we'd re-use a planner, so clear out the prior results
    open_.clear();
    closed_.clear();
    known_nodes_.clear();

    Node starting_node(start, 0, calculateHeuristic(start, goal), 0, nullptr);

    known_nodes_[starting_node.id_] = starting_node;
    open_.push_back(std::move(starting_node));

    int iters = 0;
    do {
        ++iters;
//         std::cout << "\n-----------------------\n";
//         std::cout << "Iteration " << iters << std::endl;

        // If there's nothing left to evaluate, then we have no possible path left
        if (open_.size() == 0) {
            throw std::runtime_error("A* planner could not find a path from start to goal");
        }

        // Look for Node with the lowest-F-score on the open list. Switch it to closed,
        // and hang onto it -- this is our latest node.
        Node& current(popAndClose());

        //std::cout << "Open list\n";
        //printOpenList();
        //std::cout << "Closed list\n";
        //printClosedList();
        //std::cout << "\nCurrent is " << current << std::endl;

        // Is our current state the goal state? If so, we've found a path, yay.
        if (current.ws_.meetsGoal(goal)) {
            std::vector<Action> the_plan;
            do {
                the_plan.push_back(*current.action_);
                current = known_nodes_.at(current.parent_id_);
            } while (current.parent_id_ != 0);
            return the_plan;
        }

        for (auto& action : actions) {
            // for each node REACHABLE from "me":
            if (action.eligibleFor(current.ws_)) {
                WorldState possibility = action.actOn(current.ws_);
                //std::cout << "Hmm, " << action.name() << " could work..." << "resulting in " << possibility << std::endl;

                //   if closed, next
                if (memberOfClosed(possibility)) {
                    //std::cout << "...but that one's closed out.\n";
                    continue;
                }

                auto needle = memberOfOpen(possibility);
                if (needle==end(open_)) {
                    //   if not on open list,
                    //     make me its parent
                    //     record f,g,h for it
                    Node found(possibility, current.g_ + action.cost(), calculateHeuristic(possibility, goal), current.id_, &action);
                    known_nodes_[found.id_] = found;

                    //     add to open list, mainining the sort-by-F order there
                    addToOpenList(std::move(found));
                } else {
                    //     if my path to it is better (G),
                    if ((current.g_ + action.cost()) < needle->g_) {
                        //std::cout << "My path is better\n";
                        needle->parent_id_ = current.id_;                     //       make me its parent
                        needle->g_ = current.g_ + action.cost();              //       recalc F,G for it
                        needle->h_ = calculateHeuristic(possibility, goal);
                        std::sort(open_.begin(), open_.end());                //       resort open list to account for new F
                    }
                }
            }
        }
    } while (true);

}
