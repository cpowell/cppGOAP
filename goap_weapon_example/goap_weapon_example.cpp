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

    // Action strings
    const std::string scout_stealthily("scoutStealthily");
    const std::string scout_running("scoutRunning");
    const std::string approach_enemy("approachEnemy");
    const std::string load_gun("loadGun");
    const std::string draw_gun("drawGun");
    const std::string draw_knife("drawKnife");
    const std::string shoot_enemy("shootEnemy");
    const std::string knife_enemy("knifeEnemy");
    const std::string self_destruct("selfDestruct")
    ;
    // State strings
    const std::string enemy_sighted("enemySighted");
    const std::string enemy_dead("enemyDead");
    const std::string enemy_in_range("enemyInWeaponRange");
    const std::string gun_drawn("gunDrawn");
    const std::string gun_loaded("gunLoaded");

    Action scout(scout_stealthily, 5);
    scout.setPrecondition(enemy_sighted, false);
    scout.setEffect(enemy_sighted, true);
    actions.push_back(scout);

    Action run(scout_running, 15);
    run.setPrecondition(enemy_sighted, false);
    run.setEffect(enemy_sighted, true);
    actions.push_back(run);

    Action approach(approach_enemy, 2);
    approach.setPrecondition(enemy_sighted, true);
    approach.setPrecondition(enemy_dead, false);
    approach.setPrecondition(enemy_in_range, false);
    approach.setEffect(enemy_in_range, true);
    actions.push_back(approach);

    Action load(load_gun, 1);
    load.setPrecondition(gun_loaded, false);
    load.setPrecondition(gun_drawn, true);
    load.setEffect(gun_loaded, true);
    actions.push_back(load);

    Action draw(draw_gun, 1);
    draw.setPrecondition(gun_drawn, false);
    draw.setEffect(gun_drawn, true);
    actions.push_back(draw);

    Action drawKnife(draw_knife, 1);
    drawKnife.setPrecondition(gun_drawn, false);
    drawKnife.setEffect(gun_drawn, true);
    actions.push_back(drawKnife);

    Action shoot(shoot_enemy, 3);
    shoot.setPrecondition(enemy_sighted, true);
    shoot.setPrecondition(enemy_dead, false);
    shoot.setPrecondition(gun_drawn, true);
    shoot.setPrecondition(gun_loaded, true);
    shoot.setPrecondition(enemy_in_range, true);
    shoot.setEffect(enemy_dead, true);
    actions.push_back(shoot);

    Action knife(knife_enemy, 3);
    knife.setPrecondition(enemy_sighted, true);
    knife.setPrecondition(enemy_dead, false);
    knife.setPrecondition(gun_drawn, true);
    knife.setPrecondition(gun_loaded, true);
    knife.setPrecondition(enemy_in_range, true);
    knife.setEffect(enemy_dead, true);
    actions.push_back(knife);

    Action destruct(self_destruct, 30);
    destruct.setPrecondition(enemy_sighted, true);
    destruct.setPrecondition(enemy_dead, false);
    destruct.setPrecondition(enemy_in_range, true);
    destruct.setEffect(enemy_dead, true);
    actions.push_back(destruct);

    WorldState goalState;
    goalState.setVariable(enemy_dead, true);

    WorldState initialState;
    initialState.setVariable(enemy_dead, false);
    initialState.setVariable(enemy_sighted, false);
    initialState.setVariable(enemy_in_range, false);
    initialState.setVariable(gun_loaded, false);
    initialState.setVariable(gun_drawn, false);

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