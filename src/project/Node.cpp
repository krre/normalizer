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

QByteArray Node::serializeToBinary() const {
    QByteArray result;
    result += m_id;
    return result;
}

QJsonValue Node::serializeToJson() const {
    QJsonObject result;
    result["id"] = m_id;
    return result;
}
