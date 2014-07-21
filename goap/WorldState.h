/**
 * @class WorldState
 * @brief A way of describing the "world" at any point in time.
 *
 * @date  July 2014
 * @copyright (c) 2014 Prylis Inc.. All rights reserved.
 */

#pragma once

#include "WorldVariable.h"

#include <vector>



class WorldState {
private:
    //std::vector<WorldVariable> vars_; // TODO

    // 0 = enemy sighted
    // 1 = enemy dead
    // 2 = enemy in weapon range
    // 3 = weapon loaded
    // 4 = weapon drawn



public:
    int priority_; // only used when the world state is a goal state
    std::string name_; // ditto

    bool state_vars_[5];
    bool var_matters_[5];
    // For now:
//  bool enemy_sighted_{ false };
//  bool enemy_dead_{ false };
//  bool enemy_in_weapon_range_{ false };
//  bool weapon_loaded_{ false };
//  bool weapon_drawn_{ false };

    WorldState();

    /**
     Confirms that this worldstate has at least one state variable "that matters".
     @return true if the state is valid, false if not
    */
    bool valid();

    /**
     Useful if this state is a goal state. It asks, does state 'other'
     meet the requirements of this goal? Takes into account not only this goal's
     state variables, but which variables matter to this goal state.
     @param other the state you are testing as having met this goal state
     @return true if it meets this goal state, false otherwise
    */
    bool metBy(const WorldState& other); //TODO better as meetsGoal() ??
    //void addVariable(WorldVariable var);
    //bool operator==(const WorldState& other) const;

    /**
     Given the other state -- and what 'matters' to the other state -- how many
     of our state variables differ from the other?
     @param other the goal state to compare against
     @return the number of state-var differences between us and them
    */
    int difference(const WorldState& other);
};

