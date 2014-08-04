/**
 * @class Node
 * @brief A node is any point on the path between staring point and ending point (inclusive)
 *
 * @date July 2014
 * @copyright (c) 2014 Prylis Inc. All rights reserved.
 */

#pragma once

#include "Action.h"
#include "WorldState.h"

struct Node {
    WorldState ws_;          //!< The state of the world at this node.
    static int last_id_;
    int id_;
    int parent_id_;
    int g_;                  //!< The cost so far.
    int h_;                  //!< The heuristic for remaining cost (don't overestimate!)
    int f() const {
        return g_ + h_;
    }
    //std::string actionname_; //!< How did we get to this node?
    //WorldState parentws_;    //!< Where did we come from?
    //Node* parent_;
    Action* action_;

    Node();
    Node(const WorldState state, int g, int h, int parent_id, Action* action);

    bool operator<(const Node& other);

    // A friend function of a class is defined outside that class' scope but it has the
    // right to access all private and protected members of the class. Even though the
    // prototypes for friend functions appear in the class definition, friends are not
    // member functions.
    friend std::ostream& operator<<(std::ostream& out, const Node& n);
};

inline std::ostream& operator<<(std::ostream& out, const Node& n) {
    out << "Node { id:" << n.id_ << " parent:" << n.parent_id_ << " F:" << n.f() << " G:" << n.g_ << " H:" << n.h_;
    out << ", " << n.ws_ << "}";
    return out;
}

/**
This comparison function object satisfies the requirements of Compare. This lets
us compare two Nodes by their F values. This is useful for
using binary_search and lower_bound to search the node lists.
https://stackoverflow.com/questions/18406479/binary-search-with-stdpair-using-a-custom-operator
*/
//struct CompareNodeByF {
//    // Here is the function that will be called by std::sort:
//    bool operator()(const Node& lhs, const Node& rhs) const {
//        return lhs.f_ < rhs.f_;
//    }
//};

