#include "Flow.h"

namespace Unit {

Flow::Flow(Node* node) : Unit(node) {

}

Unit::Kind Flow::kind() const {
    return Kind::Flow;
}

void Flow::append(Node* node) {
    m_nodes.append(node);
}

}
