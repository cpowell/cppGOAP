/**
 * @class Action
 * @brief Operates on the world state.
 *
 * @date  July 2014
 * @copyright (c) 2014 Prylis Inc.. All rights reserved.
 */

#pragma once

struct WorldState;

#include <string>
#include <unordered_map>

class Action {
private:
    std::string name_;
    int cost_;

    std::unordered_map<std::string, bool> preconditions_;

    std::unordered_map<std::string, bool> effects_;

public:
    Action();
    Action(std::string name, int cost);

    bool eligibleFor(const WorldState& ws) const;

    /**

     @param
     @return
     @exception
    */
    WorldState actOn(const WorldState& ws) const;

    void setPrecondition(const std::string& key, const bool value) {
        preconditions_[key] = value;
    }

    void setEffect(const std::string& key, const bool value) {
        effects_[key] = value;
    }

    int cost() const { return cost_; }

    std::string name() const { return name_; }
};

