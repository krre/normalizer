#include "Node.h"

Node::Node(Node* parent) : QObject(parent) {

}

Node::Id Node::id() const {
    return m_id;
}

void Node::setId(Id id) {
    m_id = id;
}

