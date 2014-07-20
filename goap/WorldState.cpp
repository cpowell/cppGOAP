#include "WorldState.h"


WorldState::WorldState() : priority_(0) {
	for (int i = 0; i < 5; ++i) {
		state_vars_[i] = false;
		var_matters_[i] = true;
	}
}


// void WorldState::addVariable(WorldVariable var) {
// 	vars_.push_back(var);
// }

//bool WorldState::operator==(const WorldState& other) const {
// 	enemy_dead_ == other.enemy_dead_ &&
// 		enemy_sighted_ == other.enemy_sighted_ &&
// 		weap
//}

bool WorldState::valid() {
	for (int i = 0; i < 5; ++i) {
		if (var_matters_[i])
			return true;
	}
	return false;
}

bool WorldState::metBy(const WorldState& other) {
	bool result = true;
	for (int i = 0; i < 5; ++i) {
		if (var_matters_[i] && state_vars_[i] != other.state_vars_[i]) {
			result = false;
		}
	}
	return result;
}
