// goap_weapon_example.cpp : Defines the entry point for the console application.
//

//int _tmain(int argc, _TCHAR* argv[])
//{
//  return 0;
//}

#include "Action.h"
#include "AStar.h"
#include "WorldState.h"

#include <iostream>
#include <vector>

int main(void) {
    std::cout << "Weapon example running...\n";
    std::vector<Action> actions;

    Action scout("scout", 5);
    scout.setPrecondition(0, false);
    scout.setEffect(0, true);
    actions.push_back(scout);

    Action approach("approach enemy", 2);
    approach.setPrecondition(0, true);
    approach.setPrecondition(1, false);
    approach.setPrecondition(2, false);
    approach.setEffect(2, true);
    actions.push_back(approach);

    Action load("load weapon", 1);
    load.setPrecondition(3, false);
    load.setPrecondition(4, true);
    load.setEffect(3, true);
    actions.push_back(load);

    Action draw("draw weapon", 1);
    draw.setPrecondition(4, false);
    draw.setEffect(4, true);
    actions.push_back(draw);

    Action attack("attack enemy", 3);
    attack.setPrecondition(0, true);
    attack.setPrecondition(1, false);
    attack.setPrecondition(2, true);
    attack.setPrecondition(3, true);
    attack.setPrecondition(4, true);
    attack.setEffect(1, true);
    actions.push_back(attack);

    WorldState goalState;

    for (int i = 0; i < 5; ++i) {
        goalState.var_matters_[i] = false;
    }

    goalState.state_vars_[1] = true;
    goalState.var_matters_[1] = true;

    WorldState initialState;

    AStar as;
    as.setStart(initialState);
    as.setGoal(goalState);
    try {
        as.plan(actions);
    }
    catch (const std::exception& ex) {
        std::cout << "Sorry, could not find a path!\n";
    }




}