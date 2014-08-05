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
    scout.setPrecondition("enemySighted", false);
    scout.setEffect("enemySighted", true);
    actions.push_back(scout);

    Action run("scout while running", 15);
    run.setPrecondition("enemySighted", false);
    run.setEffect("enemySighted", true);
    actions.push_back(run);

    Action approach("approach enemy", 2);
    approach.setPrecondition("enemySighted", true);
    approach.setPrecondition("enemyDead", false);
    approach.setPrecondition("enemyInWeaponRange", false);
    approach.setEffect("enemyInWeaponRange", true);
    actions.push_back(approach);

    Action load("load gun", 1);
    load.setPrecondition("gunLoaded", false);
    load.setPrecondition("gunDrawn", true);
    load.setEffect("gunLoaded", true);
    actions.push_back(load);

    Action draw("draw gun", 1);
    draw.setPrecondition("gunDrawn", false);
    draw.setEffect("gunDrawn", true);
    actions.push_back(draw);

    Action draw_knife("draw knife", 1);
    draw_knife.setPrecondition("gunDrawn", false);
    draw_knife.setEffect("gunDrawn", true);
    actions.push_back(draw_knife);

    Action shoot("shoot enemy", 3);
    shoot.setPrecondition("enemySighted", true);
    shoot.setPrecondition("enemyDead", false);
    shoot.setPrecondition("gunDrawn", true);
    shoot.setPrecondition("gunLoaded", true);
    shoot.setPrecondition("enemyInWeaponRange", true);
    shoot.setEffect("enemyDead", true);
    actions.push_back(shoot);

    Action knife("knife enemy", 3);
    knife.setPrecondition("enemySighted", true);
    knife.setPrecondition("enemyDead", false);
    knife.setPrecondition("gunDrawn", true);
    knife.setPrecondition("gunLoaded", true);
    knife.setPrecondition("enemyInWeaponRange", true);
    knife.setEffect("enemyDead", true);
    actions.push_back(knife);

    Action destruct("self destruct", 30);
    destruct.setPrecondition("enemySighted", true);
    destruct.setPrecondition("enemyDead", false);
    destruct.setPrecondition("enemyInWeaponRange", true);
    destruct.setEffect("enemyDead", true);
    actions.push_back(destruct);

    WorldState goalState;
    goalState.setVariable("enemyDead", true);

    WorldState initialState;
    initialState.setVariable("enemyDead", false);
    initialState.setVariable("enemySighted", false);
    initialState.setVariable("enemyInWeaponRange", false);
    initialState.setVariable("gunLoaded", false);
    initialState.setVariable("gunDrawn", false);

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