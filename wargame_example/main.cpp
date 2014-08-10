/**
* @brief an example befitting the AI of a naval wargame
*
* @date August 2014
* @copyright (c) 2014 Prylis Inc. All rights reserved.
*/

#include "Action.h"
#include "AStar.h"
#include "WorldState.h"

#include <iostream>
#include <vector>

using namespace goap;

int main(void) {
    std::cout << "Wargame example running...\n";
    std::vector<Action> actions;

    // Constants for the various states are helpful to keep us from
    // accidentally mistyping a state name.
    const int target_acquired = 10;
    const int target_lost = 15;
    const int target_in_warhead_range = 20;
    const int target_dead = 30;

    // Now establish all the possible actions for the action pool
    // In this example we're providing the AI some different FPS actions
    Action spiral("searchSpiral", 5);
    spiral.setPrecondition(target_acquired, false);
    spiral.setPrecondition(target_lost, true);
    spiral.setEffect(target_acquired, true);
    actions.push_back(spiral);

    Action serpentine("searchSerpentine", 5);
    serpentine.setPrecondition(target_acquired, false);
    serpentine.setPrecondition(target_lost, false);
    serpentine.setEffect(target_acquired, true);
    actions.push_back(serpentine);

    Action intercept("interceptTarget", 5);
    intercept.setPrecondition(target_acquired, true);
    intercept.setPrecondition(target_dead, false);
    intercept.setEffect(target_in_warhead_range, true);
    actions.push_back(intercept);

    Action detonateNearTarget("detonateNearTarget", 5);
    detonateNearTarget.setPrecondition(target_in_warhead_range, true);
    detonateNearTarget.setPrecondition(target_acquired, true);
    detonateNearTarget.setPrecondition(target_dead, false);
    detonateNearTarget.setEffect(target_dead, true);
    actions.push_back(detonateNearTarget);

    // Here's the initial state...
    WorldState initial_state;
    initial_state.setVariable(target_acquired, false);
    initial_state.setVariable(target_lost, true);
    initial_state.setVariable(target_in_warhead_range, false);
    initial_state.setVariable(target_dead, false);

    // ...and the goal state
    WorldState goal_target_dead;
    goal_target_dead.setVariable(target_dead, true);
    goal_target_dead.priority_ = 50;

    // Fire up the A* planner
    AStar as;
    as.setStart(initial_state);
    as.setGoal(goal_target_dead);

    try {
        as.plan(actions);
    }
    catch (const std::exception&) {
        std::cout << "Sorry, could not find a path!\n";
    }

}