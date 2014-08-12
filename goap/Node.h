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

namespace goap {
    struct Node {
        static int last_id_; // a static that lets us assign incrementing, unique IDs to nodes

        WorldState ws_;      // The state of the world at this node.
        int id_;             // the unique ID of this node
        int parent_id_;      // the ID of this node's immediate predecessor
        int g_;              // The A* cost from 'start' to 'here'
        int h_;              // The estimated remaining cost to 'goal' form 'here'
        const Action* action_;     // The action that got us here (for replay purposes)

        Node();
        Node(const WorldState state, int g, int h, int parent_id, const Action* action);

        // F -- which is simply G+H -- is autocalculated
        int f() const {
            return g_ + h_;
        }

        /**
         Less-than operator, needed for keeping Nodes sorted.
         @param other the other node to compare against
         @return true if this node is less than the other (using F)
         */
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

}