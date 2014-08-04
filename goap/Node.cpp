#include "Node.h"

int Node::last_id_ = 0;

Node::Node() : g_(0), h_(0) {
    id_ = ++last_id_;
}
Node::Node(const WorldState state, int g, int h, int parent_id, Action* action) :
    ws_(state), g_(g), h_(h), parent_id_(parent_id), action_(action) {
    id_ = ++last_id_;
}

bool Node::operator<(const Node& other) {
    return f() < other.f();
}
