#include "Action.h"
#include "WorldState.h"

Action::Action() : cost_(0) {
    for (int i = 0; i < 5; ++i) {
        preconditions_[i] = false;
        precondition_matters_[i] = false;
        effects_[i] = false;
        has_effect_[i] = false;
    }
}

Action::Action(std::string name, int cost) : Action() {
    // Because delegating constructors cannot initialize & delegate at the same time...
    name_ = name;
    cost_ = cost;
}

bool Action::eligibleFor(const WorldState& ws) const {
    for (int i = 0; i < 5; ++i) {
        if (precondition_matters_[i] && ws.state_vars_[i] != preconditions_[i]) {
            return false;
        }
    }

    return true;
}

WorldState Action::actOn(const WorldState& ws) const {
    WorldState tmp(ws); // make a copy, which correctly deep-copies the array members
    if (eligibleFor(ws)) {
        for (int i = 0; i < 5; ++i) {
            if (has_effect_[i]) {
                tmp.state_vars_[i] = effects_[i];
            }
        }
    }
    return tmp;
}

