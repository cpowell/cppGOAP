/**
 * @brief an example befitting the AI of a shooter game
 *
 * @date August 2014
 * @copyright (c) 2014 Prylis Inc. All rights reserved.
 */

#include "Action.h"
#include "AStar.h"
#include "WorldState.h"

#include <iostream>
#include <vector>

int main(void) {
    std::cout << "Weapon example running...\n";
    std::vector<Action> actions;

    // Constants for the various states are helpful to keep us from
    // accidentally mistyping a state name.
    const int enemy_sighted = 1;
    const int enemy_dead = 2;
    const int enemy_in_range = 3;
    const int enemy_in_close_range = 4;
    const int inventory_knife = 5;
    const int inventory_gun = 6;
    const int gun_drawn = 7;;
    const int gun_loaded = 8;
    const int have_ammo = 9;
    const int knife_drawn = 10;
    const int weapon_in_hand = 11;
    const int me_dead = 12;

    // Now establish all the possible actions for the action pool
    // In this example we're providing the AI some different FPS actions
    Action scout("scoutStealthily", 5);
    scout.setPrecondition(enemy_sighted, false);
    scout.setPrecondition(weapon_in_hand, true);
    scout.setEffect(enemy_sighted, true);
    actions.push_back(scout);

    Action run("scoutRunning", 15);
    run.setPrecondition(enemy_sighted, false);
    scout.setPrecondition(weapon_in_hand, true);
    run.setEffect(enemy_sighted, true);
    actions.push_back(run);

    Action approach("closeToGunRange", 2);
    approach.setPrecondition(enemy_sighted, true);
    approach.setPrecondition(enemy_dead, false);
    approach.setPrecondition(enemy_in_range, false);
    approach.setPrecondition(gun_loaded, true);
    approach.setEffect(enemy_in_range, true);
    actions.push_back(approach);

    Action approachClose("closeToKnifeRange", 4);
    approachClose.setPrecondition(enemy_sighted, true);
    approachClose.setPrecondition(enemy_dead, false);
    approachClose.setPrecondition(enemy_in_close_range, false);
    approachClose.setEffect(enemy_in_close_range, true);
    actions.push_back(approachClose);

    Action load("loadGun", 2);
    load.setPrecondition(have_ammo, true);
    load.setPrecondition(gun_loaded, false);
    load.setPrecondition(gun_drawn, true);
    load.setEffect(gun_loaded, true);
    load.setEffect(have_ammo, false);
    actions.push_back(load);

    Action draw("drawGun", 1);
    draw.setPrecondition(inventory_gun, true);
    draw.setPrecondition(weapon_in_hand, false);
    draw.setPrecondition(gun_drawn, false);
    draw.setEffect(gun_drawn, true);
    draw.setEffect(weapon_in_hand, true);
    actions.push_back(draw);

    Action holster("holsterGun", 1);
    holster.setPrecondition(weapon_in_hand, true);
    holster.setPrecondition(gun_drawn, true);
    holster.setEffect(gun_drawn, false);
    holster.setEffect(weapon_in_hand, false);
    actions.push_back(holster);

    Action drawKnife("drawKnife", 1);
    drawKnife.setPrecondition(inventory_knife, true);
    drawKnife.setPrecondition(weapon_in_hand, false);
    drawKnife.setPrecondition(knife_drawn, false);
    drawKnife.setEffect(knife_drawn, true);
    drawKnife.setEffect(weapon_in_hand, true);
    actions.push_back(drawKnife);

    Action sheath("sheathKnife", 1);
    sheath.setPrecondition(weapon_in_hand, true);
    sheath.setPrecondition(knife_drawn, true);
    sheath.setEffect(knife_drawn, false);
    sheath.setEffect(weapon_in_hand, false);
    actions.push_back(sheath);

    Action shoot("shootEnemy", 3);
    shoot.setPrecondition(enemy_sighted, true);
    shoot.setPrecondition(enemy_dead, false);
    shoot.setPrecondition(gun_drawn, true);
    shoot.setPrecondition(gun_loaded, true);
    shoot.setPrecondition(enemy_in_range, true);
    shoot.setEffect(enemy_dead, true);
    actions.push_back(shoot);

    Action knife("knifeEnemy", 3);
    knife.setPrecondition(enemy_sighted, true);
    knife.setPrecondition(enemy_dead, false);
    knife.setPrecondition(knife_drawn, true);
    knife.setPrecondition(enemy_in_close_range, true);
    knife.setEffect(enemy_dead, true);
    actions.push_back(knife);

    Action destruct("selfDestruct", 30);
    destruct.setPrecondition(enemy_sighted, true);
    destruct.setPrecondition(enemy_dead, false);
    destruct.setPrecondition(enemy_in_range, true);
    destruct.setEffect(enemy_dead, true);
    destruct.setEffect(me_dead, true);
    actions.push_back(destruct);

    // Now establish some goal states and an initial state
    WorldState goalStateDraw;
    goalStateDraw.setVariable(enemy_dead, true);
    goalStateDraw.setVariable(me_dead, true);
    goalStateDraw.priority_ = 50;

    WorldState goalStateWin;
    goalStateWin.setVariable(enemy_dead, true);
    goalStateWin.setVariable(me_dead, false);
    goalStateWin.setVariable(weapon_in_hand, true);
    goalStateWin.priority_ = 100;

    // You can tweak these (e.g. have_ammo, the inventory items) to
    // elicit different plans from the AI.
    WorldState initialState;
    initialState.setVariable(enemy_dead, false);
    initialState.setVariable(enemy_sighted, false);
    initialState.setVariable(enemy_in_range, false);
    initialState.setVariable(enemy_in_close_range, false);
    initialState.setVariable(gun_loaded, false);
    initialState.setVariable(gun_drawn, false);
    initialState.setVariable(knife_drawn, false);
    initialState.setVariable(weapon_in_hand, false);
    initialState.setVariable(me_dead, false);
    initialState.setVariable(have_ammo, true);
    initialState.setVariable(inventory_knife, true);
    initialState.setVariable(inventory_gun, true);

    // Fire up the A* planner
    AStar as;
    as.setStart(initialState);
    as.setGoal(goalStateWin);

    try {
        as.plan(actions);
    }
    catch (const std::exception&) {
        std::cout << "Sorry, could not find a path!\n";
    }

//     as.setGoal(goalStateDraw);
//     try {
//         as.plan(actions);
//     }
//     catch (const std::exception& ex) {
//         std::cout << "Sorry, could not find a path!\n";
//     }



}