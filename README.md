# C++ GOAP
A simple GOAP (goal-oriented action planner) useful for game AI

## Note
This GOAP planner is inspired by Jeff Orkin's writings at http://alumni.media.mit.edu/~jorkin/goap.html .
I wholeheartedly encourage you to read his papers there about how he and his team implemented AI in "F.E.A.R." using GOAP.

The planner works well and fulfills the typical behaviors. Please consider it a work-in-progress as I add improvements, benchmark and optimize it, etc.

## Goal-Oriented Action Planning

Whereas some AI constructs like the fuzzy-logic FAM help you decide "what to do", GOAP helps you decide "how to do it." The planner is able to do this from a few basic ingredients:
* A starting state
* A goal state
* A basket of actions that it can take, each of which has preconditions and effects

The neat thing about a GOAP planner is that it figures out the 'route' from start to goal entirely by itself. It constructs said route by treating each 
worldstate as a 'node' on a possible path, and employs the common A* ("A-star") pathfinding algorithm to find the best "path" between the states.

## Building and running

This code leverages the C++11 standard. Visual Studio 2012 (or newer) is required to build the included solution; the code can also be easily adapted to build in XCode or using Clang/LLVM. (Consider these on my to-do list.)

## Included example

As Jeff Orkin's paper used a FPS AI, I've written an example that emulates the AI of a shooter. Here's an example run:

	Weapon example running...
	Found a path!
	knifeEnemy yields WorldState { isEnemyDead:1 | isMeDead:0 | hasWeaponInHand:1 | isEnemySighted:1 | isGunDrawn:0 | hasGun:1 | isEnemyInGunRange:0 | isKnifeDrawn:1 | isEnemyInKnifeRange:1 | isGunLoaded:0 | hasGunAmmo: 1 | hasKnife:1 | }
	closeToKnifeRange yields WorldState { isEnemyDead:0 | isMeDead:0 | hasWeaponInHand:1 | isEnemySighted:1 | isGunDrawn:0 | isEnemyInGunRange:0 | hasGun:1 | isKnifeDrawn:1 | isEnemyInKnifeRange:1 | isGunLoaded:0 | hasGunAmmo:1 | hasKnife:1 | }
	scoutStealthily yields WorldState { isEnemyDead:0 | isMeDead:0 | hasWeaponInHand:1 | isEnemySighted:1 | isGunDrawn:0 | isEnemyInGunRange:0 | hasGun:1 | isKnifeDrawn:1 | isEnemyInKnifeRange:0 | isGunLoaded:0 | hasGunAmmo:1 | hasKnife:1 | }
	drawKnife yields WorldState { isEnemyDead:0 | isMeDead:0 | hasWeaponInHand:1 | isEnemySighted:0 | isGunDrawn:0 | hasGun:1 | isEnemyInGunRange:0 | isKnifeDrawn:1 | isEnemyInKnifeRange:0 | isGunLoaded:0 | hasGunAmmo:1 | hasKnife:1 | }

In its present form it's somewhat verbose for use as a teaching tool and for experimentation; for even greater verbosity you can uncomment various ```std::cout``` calls in AStar.cpp. For actual use in a game (instead of as a toy or teaching tool) you would suppress all output and simply use the results in code.
