#include "Action.h"
#include "WorldState.h"

Action::Action() : cost_(0) {
}

Action::Action(std::string name, int cost) : Action() {
    // Because delegating constructors cannot initialize & delegate at the same time...
    name_ = name;
    cost_ = cost;
}

bool Action::eligibleFor(const WorldState& ws) const {
    for (const auto& precond : preconditions_) {
        try {
            if (ws.vars_.at(precond.first) != precond.second) {
                return false;
            }
        }
        catch (const std::out_of_range&) {
            return false;
        }
    }
    return true;
}

WorldState Action::actOn(const WorldState& ws) const {
    WorldState tmp(ws);
    if (eligibleFor(ws)) {
        for (const auto& effect : effects_) {
            tmp.setVariable(effect.first, effect.second);
        }
    }
    return tmp;
}

