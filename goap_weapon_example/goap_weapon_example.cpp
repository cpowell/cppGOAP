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

    // State strings
    const std::string enemy_sighted("isEnemySighted");
    const std::string enemy_dead("isEnemyDead");
    const std::string enemy_in_range("isEnemyInGunRange");
    const std::string enemy_in_close_range("isEnemyInKnifeRange");
    const std::string gun_drawn("isGunDrawn");
    const std::string gun_loaded("isGunLoaded");
    const std::string knife_drawn("isKnifeDrawn");
    const std::string weapon_in_hand("isWeaponInHand");
    const std::string me_dead("isMeDead");

    Action scout("scoutStealthily", 5);
    scout.setPrecondition(enemy_sighted, false);
    scout.setEffect(enemy_sighted, true);
    actions.push_back(scout);

    Action run("scoutRunning", 15);
    run.setPrecondition(enemy_sighted, false);
    run.setEffect(enemy_sighted, true);
    actions.push_back(run);

    Action approach("closeToGunRange", 2);
    approach.setPrecondition(enemy_sighted, true);
    approach.setPrecondition(enemy_dead, false);
    approach.setPrecondition(enemy_in_range, false);
    approach.setEffect(enemy_in_range, true);
    actions.push_back(approach);

    Action approachClose("closeToKnifeRange", 4);
    approachClose.setPrecondition(enemy_sighted, true);
    approachClose.setPrecondition(enemy_dead, false);
    approachClose.setPrecondition(enemy_in_close_range, false);
    approachClose.setEffect(enemy_in_close_range, true);
    actions.push_back(approachClose);

    Action load("loadGun", 2);
    load.setPrecondition(gun_loaded, false);
    load.setPrecondition(gun_drawn, true);
    load.setEffect(gun_loaded, true);
    actions.push_back(load);

    Action draw("drawGun", 1);
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
    drawKnife.setPrecondition(weapon_in_hand, false);
    drawKnife.setPrecondition(gun_drawn, false);
    drawKnife.setEffect(gun_drawn, true);
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

    WorldState goalStateDraw;
    goalStateDraw.setVariable(enemy_dead, true);
    goalStateDraw.setVariable(me_dead, true);
    goalStateDraw.priority_ = 50;

    WorldState goalStateWin;
    goalStateWin.setVariable(enemy_dead, true);
    goalStateWin.setVariable(me_dead, false);
    goalStateWin.setVariable(weapon_in_hand, true);
    goalStateWin.priority_ = 100;

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

    AStar as;
    as.setStart(initialState);
    as.setGoal(goalStateWin);
    try {
        as.plan(actions);
    }
    catch (const std::exception& ex) {
        std::cout << "Sorry, could not find a path!\n";
    }

    as.setGoal(goalStateDraw);
    try {
        as.plan(actions);
    }
    catch (const std::exception& ex) {
        std::cout << "Sorry, could not find a path!\n";
    }



}