// goap_weapon_example.cpp : Defines the entry point for the console application.
//

//int _tmain(int argc, _TCHAR* argv[])
//{
//  return 0;
//}

#include "Action.h"
#include "WorldState.h"

#include <iostream>
#include <vector>

int main(void) {
    std::cout << "Weapon example running...\n";
    std::vector<Action> actions;

    Action scout;
    scout.setEffect(0, true);
    scout.setName("scout");
    actions.push_back(scout);

    Action approach;
    approach.setName("approach enemy");
    approach.setPrecondition(0, true);
    approach.setEffect(2, true);
    actions.push_back(approach);

    Action load;
    load.setName("load weapon");
    load.setPrecondition(4, true);
    load.setEffect(3, true);
    actions.push_back(load);

    Action draw;
    draw.setName("draw weapon");
    draw.setEffect(3, true);
    actions.push_back(draw);

    Action attack;
    attack.setName("attack enemy");
    attack.setPrecondition(0, true);
    attack.setPrecondition(1, false);
    attack.setPrecondition(2, true);
    attack.setPrecondition(3, true);
    attack.setPrecondition(4, true);
    actions.push_back(attack);

    WorldState goalState;

    for (int i = 0; i < 5; ++i) {
        goalState.var_matters_[i] = false;
    }

    goalState.state_vars_[1] = true;
    goalState.var_matters_[1] = true;

    WorldState initialState;
    initialState.state_vars_[0] = false;




}