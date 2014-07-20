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

bool Action::eligibleFor(const WorldState& node) {
	for (int i = 0; i < 5; ++i) {
		if (precondition_matters_[i] && node.state_vars_[i] != preconditions_[i])
			return false;
	}
	return true;
}

WorldState Action::actOn(const WorldState& node) {
	WorldState tmp(node); // make a copy, which correctly deep-copies the array members
	for (int i = 0; i < 5; ++i) {
		if (has_effect_[i])
			tmp.state_vars_[i] = effects_[i];
	}
	return tmp;
}

