#include "AStar.h"

#include <algorithm>
#include <iostream>

AStar::AStar() {
}

int AStar::calculateHeuristic(const WorldState& now, const WorldState& goal) const {
    return now.difference(goal);
}

void AStar::addToOpenList(Node&& n) {
    // insert maintaining sort order
    auto it = std::lower_bound(begin(open_),
                               end(open_),
                               n);
    open_.emplace(it, std::move(n));
}

Node& AStar::popAndClose() {
    if (open_.size() == 0) {
        throw std::invalid_argument("You cannot call popAndClose on an empty open-list!");
    }

    closed_.push_back(std::move(open_.front()));
    open_.erase(open_.begin());

    return closed_.back();
}

bool AStar::memberOfClosed(const WorldState& ws) const {
    for (const auto& node : closed_) {
        if (node.ws_ == ws) {
            return true;
        }
    }
    return false;
}

bool AStar::memberOfOpen(const WorldState& ws) const {
    for (const auto& node : open_) {
        if (node.ws_ == ws) {
            return true;
        }
    }
    return false;
}

void AStar::printOpenList() const {

    for (const auto& n : open_) {
        std::cout << n << std::endl;
    }
}

void AStar::printClosedList() const {

    for (const auto& n : closed_) {
        std::cout << n << std::endl;
    }
}

void AStar::plan(std::vector<Action>& actions) {
    Node n(start_, 0, calculateHeuristic(start_, goal_), 0, nullptr);

    known_nodes_[n.id_] = n;
    open_.push_back(std::move(n));

    int iters = 0;
    do {
        ++iters;
        std::cout << "\n-----------------------\n";
        std::cout << "Iteration " << iters << std::endl;

        // If there's nothing left to evaluate, then we have no possible path left
        if (open_.size() == 0) {
            throw std::runtime_error("Could not find a path");
        }

        // Look for Node with the lowest-F-score on the open list. Switch it to closed,
        // and hang onto it -- this is our latest node.
        Node& latest(popAndClose());

//         std::cout << "Open list\n";
//         printOpenList();
//         std::cout << "Closed list\n";
//         printClosedList();

        std::cout << "\nLatest is " << latest << std::endl;

        // Is our latest state the goal state? If so, we've found a path, yay.
        if (goal_.metBy(latest.ws_)) {
            std::cout << "Found a path!\n";
            do {
                std::cout << latest.action_->name() << " yields " << latest.ws_ << std::endl;
                latest = known_nodes_.at(latest.parent_id_);
            } while (latest.parent_id_ != 0);
            break;
        }

        for (auto& action : actions) {
            // for each node REACHABLE from "me":
            if (action.eligibleFor(latest.ws_)) {
                std::cout << "Hmm, " << action.name() << " could work...";
                WorldState possibility = action.actOn(latest.ws_);
                std::cout << "resulting in " << possibility << std::endl;

                //   if closed, next
                if (memberOfClosed(possibility)) {
                    std::cout << "...but that one's closed out.\n";
                    continue;
                }

                //   if not on open list,
                if (!memberOfOpen(possibility)) {
                    //     make me its parent
                    //     record f,g,h for it
                    Node found(possibility, (latest.g_ + action.cost()), (calculateHeuristic(possibility, goal_)), latest.id_, &action);
                    known_nodes_[found.id_] = found;

                    //     add to open list, mainining the sort-by-F order there
                    addToOpenList(std::move(found));
                } else {
                    //FIXME
                    //     if my path to it is better (G),
                    //       make me its parent
                    //       recalc F,G for it
                    //       resort open list to account for new F
                }
            }
        }
    } while (true);

}


// for each node REACHABLE from "me":
//   if closed, next
//   if not on open list,
//     add to open list
//     make me its parent
//     record f,g,h for it
//   else (i.e. already on open list)
//     if my path to it is better (G),
//       make me its parent
//       recalc F,G for it
//       resort open list to account for new F


//         c) For each of the 8 squares adjacent to this current square …
//
//             If it is not walkable or if it is on the closed list, ignore it.Otherwise do the following.
//
//             If it isn’t on the open list, add it to the open list.Make the current square the parent of this square.Record the F, G, and H costs of the square.
//
//             If it is on the open list already, check to see if this path to that square is better, using G cost as the measure.
//A lower G cost means that this is a better path.If so, change the parent of the square to the current square,
//and recalculate the G and F scores of the square.If you are keeping your open list sorted by F score, you may
//need to resort the list to account for the change.
//
//             d) Stop when you :
//
//         Add the target square to the closed list, in which case the path has been found(see note below), or
//             Fail to find the target square, and the open list is empty.In this case, there is no path.


// 3) Save the path. Working backwards from the target square, go from each square to its parent square
// until you reach the starting square. That is your path.
