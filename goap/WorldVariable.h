/**
 * @class WorldVariable
 * @brief one of the variables that collectively make up a WorldState
 *
 * @date  July 2014
 * @copyright (c) 2014 Prylis Inc.. All rights reserved.
 */

#pragma once

#include <string>

class WorldVariable {
private:
	bool value_;
	std::string name_;

public:
	WorldVariable(const std::string& name, const bool value);
};

