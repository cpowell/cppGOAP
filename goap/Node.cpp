#include "Node.h"

Node::Node() : g_(0), h_(0), f_(0) {
    //nop
}
Node::Node(WorldState& state, int g, int h, int f, WorldState& parent) :
    ws_(state), g_(g), h_(h), f_(f), parentws_(parent) {
    //nop
}