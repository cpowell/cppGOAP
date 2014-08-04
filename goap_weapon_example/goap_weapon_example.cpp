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

    Action scout("scout stealthily", 5);
    scout.setPrecondition(0, false);
    scout.setEffect(0, true);
    actions.push_back(scout);

    Action run("scout while running", 15);
    run.setPrecondition(0, false);
    run.setEffect(0, true);
    actions.push_back(run);

    Action approach("approach enemy", 2);
    approach.setPrecondition(0, true);
    approach.setPrecondition(1, false);
    approach.setPrecondition(2, false);
    approach.setEffect(2, true);
    actions.push_back(approach);

    Action load("load gun", 1);
    load.setPrecondition(3, false);
    load.setPrecondition(4, true);
    load.setEffect(3, true);
    actions.push_back(load);

    Action draw("draw gun", 1);
    draw.setPrecondition(4, false);
    draw.setEffect(4, true);
    actions.push_back(draw);

    Action draw_knife("draw knife", 1);
    draw_knife.setPrecondition(4, false);
    draw_knife.setEffect(4, true);
    actions.push_back(draw_knife);

    Action shoot("shoot enemy", 3);
    shoot.setPrecondition(0, true);
    shoot.setPrecondition(1, false);
    shoot.setPrecondition(2, true);
    shoot.setPrecondition(3, true);
    shoot.setPrecondition(4, true);
    shoot.setEffect(1, true);
    actions.push_back(shoot);

    Action knife("knife enemy", 3);
    knife.setPrecondition(0, true);
    knife.setPrecondition(1, false);
    knife.setPrecondition(2, true);
    knife.setPrecondition(4, true);
    knife.setEffect(1, true);
    actions.push_back(knife);

    Action destruct("self destruct", 30);
    destruct.setPrecondition(0, true);
    destruct.setPrecondition(1, false);
    destruct.setPrecondition(2, true);
    destruct.setEffect(1, true);
    actions.push_back(destruct);

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