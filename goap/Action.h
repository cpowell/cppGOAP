/**
 * @class Action
 * @brief Operates on the world state.
 *
 * @date  July 2014
 * @copyright (c) 2014 Prylis Inc.. All rights reserved.
 */

#pragma once

class WorldState;

#include <string>

class Action {
private:
    std::string name_;
    int cost_;

    bool preconditions_[5];
    bool precondition_matters_[5];

    bool effects_[5];
    bool has_effect_[5];

public:
    Action();

    bool eligibleFor(const WorldState& node);
    WorldState actOn(const WorldState& node);

    void setPrecondition(int index, bool value) {
        preconditions_[index] = value; // TODO yeah this should be range checked
    }

    void setEffect(int index, bool value) {
        effects_[index] = value; // TODO range check
    }

    void setName(std::string name) {
        name_ = name;
    }

    std::string name() { return name_; }
};

