#include "WorldState.h"

WorldState::WorldState() : priority_(0) {
    for (int i = 0; i < 5; ++i) {
        state_vars_[i] = false;
        var_matters_[i] = true;
    }
}

bool WorldState::operator==(const WorldState& other) const {
    for (int i = 0; i < 5; ++i) {
        if (state_vars_[i] != other.state_vars_[i]) {
            return false;
        }
    }

    return true;
}


bool WorldState::valid() const {
    for (int i = 0; i < 5; ++i) {
        if (var_matters_[i]) {
            return true;
        }
    }

    return false;
}

bool WorldState::metBy(const WorldState& other) const {
    for (int i = 0; i < 5; ++i) {
        if (var_matters_[i] && state_vars_[i] != other.state_vars_[i]) {
            return false;
        }
    }

    return true;
}

int WorldState::difference(const WorldState& other) const {
    int result = 0;

    for (int i = 0; i < 5; ++i) {
        if (other.var_matters_[i] && state_vars_[i] != other.state_vars_[i]) {
            ++result;
        }
    }

    return result;
}