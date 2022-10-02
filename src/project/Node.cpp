#include "Node.h"
#include <QJsonObject>

Node::Node(Node* parent) : QObject(parent) {

}

Node::Id Node::id() const {
    return m_id;
}

void Node::setId(Id id) {
    m_id = id;
}

QJsonValue Node::serializeToJson() const {
    return { { "id", m_id } };
}
