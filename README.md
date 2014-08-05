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
