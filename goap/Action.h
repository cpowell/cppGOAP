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
    Action(std::string name, int cost);

    bool eligibleFor(const WorldState& ws) const;
    WorldState actOn(const WorldState& ws) const;

    void setPrecondition(const int index, const bool value) {
        preconditions_[index] = value; // TODO yeah this should be range checked
        precondition_matters_[index] = true;
    }

    void setEffect(const int index, const bool value) {
        effects_[index] = value; // TODO range check
        has_effect_[index] = true;
    }

    void setName(const std::string name) {
        name_ = name;
    }

    int cost() const { return cost_; }
    std::string name() const { return name_; }
};

