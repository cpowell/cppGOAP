#include "Node.h"

Node::Node() : g_(0), h_(0), f_(0) {
    //nop
}
Node::Node(WorldState& state, int g, int h, int f, Node* parent) :
    ws_(state), g_(g), h_(h), f_(f), parent_(parent) {
    //nop
}

bool Node::operator<(const Node& other) {
    return f_ < other.f_;
}
