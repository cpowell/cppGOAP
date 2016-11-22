#include "Planner.h"

#include <algorithm>
#include <cassert>
#include <iostream>

goap::Planner::Planner() {
}

int goap::Planner::calculateHeuristic(const WorldState& now, const WorldState& goal) const {
    return now.distanceTo(goal);
}

void goap::Planner::addToOpenList(Node&& n) {
    // insert maintaining sort order
    auto it = std::lower_bound(begin(open_),
                               end(open_),
                               n);
    open_.emplace(it, std::move(n));
}

goap::Node& goap::Planner::popAndClose() {
    assert(!open_.empty());
    closed_.push_back(std::move(open_.front()));
    open_.erase(open_.begin());

    return closed_.back();
}

bool goap::Planner::memberOfClosed(const WorldState& ws) const {
    if (std::find_if(begin(closed_), end(closed_), [&](const Node & n) { return n.ws_ == ws; }) == end(closed_)) {
        return false;
    }
    return true;
}

std::vector<goap::Node>::iterator goap::Planner::memberOfOpen(const WorldState& ws) {
    return std::find_if(begin(open_), end(open_), [&](const Node & n) { return n.ws_ == ws; });
}

void goap::Planner::printOpenList() const {
    for (const auto& n : open_) {
        std::cout << n << std::endl;
    }
}

void goap::Planner::printClosedList() const {
    for (const auto& n : closed_) {
        std::cout << n << std::endl;
    }
}

std::vector<goap::Action> goap::Planner::plan(const WorldState& start, const WorldState& goal, const std::vector<Action>& actions) {
    if (start.meetsGoal(goal)) {
        //throw std::runtime_error("Planner cannot plan when the start state and the goal state are the same!");
        return std::vector<goap::Action>();
    }

    // Feasible we'd re-use a planner, so clear out the prior results
    open_.clear();
    closed_.clear();

    Node starting_node(start, 0, calculateHeuristic(start, goal), 0, nullptr);

    open_.push_back(std::move(starting_node));

    //int iters = 0;
    while (open_.size() > 0) {
        //++iters;
        //std::cout << "\n-----------------------\n";
        //std::cout << "Iteration " << iters << std::endl;

        // Look for Node with the lowest-F-score on the open list. Switch it to closed,
        // and hang onto it -- this is our latest node.
        Node& current(popAndClose());

        //std::cout << "Open list\n";
        //printOpenList();
        //std::cout << "Closed list\n";
        //printClosedList();
        //std::cout << "\nCurrent is " << current << " : " << (current.action_ == nullptr ? "" : current.action_->name()) << std::endl;

        // Is our current state the goal state? If so, we've found a path, yay.
        if (current.ws_.meetsGoal(goal)) {
            std::vector<Action> the_plan;
            do {
                the_plan.push_back(*current.action_);
                auto itr = std::find_if(begin(open_), end(open_), [&](const Node & n) { return n.id_ == current.parent_id_; });
                if (itr == end(open_)) {
                    itr = std::find_if(begin(closed_), end(closed_), [&](const Node & n) { return n.id_ == current.parent_id_; });
                }
                current = *itr;
            } while (current.parent_id_ != 0);
            return the_plan;
        }

        // Check each node REACHABLE from current -- in other words, where can we go from here?
        for (const auto& potential_action : actions) {
            if (potential_action.operableOn(current.ws_)) {
                WorldState outcome = potential_action.actOn(current.ws_);

                // Skip if already closed
                if (memberOfClosed(outcome)) {
                    continue;
                }

                //std::cout << potential_action.name() << " will get us to " << outcome << std::endl;

                // Look for a Node with this WorldState on the open list.
                auto p_outcome_node = memberOfOpen(outcome);
                if (p_outcome_node == end(open_)) { // not a member of open list
                    // Make a new node, with current as its parent, recording G & H
                    Node found(outcome, current.g_ + potential_action.cost(), calculateHeuristic(outcome, goal), current.id_, &potential_action);
                    // Add it to the open list (maintaining sort-order therein)
                    addToOpenList(std::move(found));
                } else { // already a member of the open list
                    // check if the current G is better than the recorded G
                    if (current.g_ + potential_action.cost() < p_outcome_node->g_) {
                        //std::cout << "My path to " << p_outcome_node->ws_ << " using " << potential_action.name() << " (combined cost " << current.g_ + potential_action.cost() << ") is better than existing (cost " <<  p_outcome_node->g_ << "\n";
                        p_outcome_node->parent_id_ = current.id_;                  // make current its parent
                        p_outcome_node->g_ = current.g_ + potential_action.cost(); // recalc G & H
                        p_outcome_node->h_ = calculateHeuristic(outcome, goal);
                        p_outcome_node->action_ = &potential_action;

                        // resort open list to account for the new F
                        // sorting likely invalidates the p_outcome_node iterator, but we don't need it anymore
                        std::sort(begin(open_), end(open_));
                    }
                }
            }
        }
    }

    // If there's nothing left to evaluate, then we have no possible path left
    throw std::runtime_error("A* planner could not find a path from start to goal");
}
