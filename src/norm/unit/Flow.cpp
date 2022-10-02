#include "Flow.h"
#include <QJsonArray>

namespace Unit {

Flow::Flow(Node* node) : Unit(node) {

}

Unit::Kind Flow::kind() const {
    return Kind::Flow;
}

void Flow::append(Node* node) {
    m_nodes.append(node);
}

QJsonValue Flow::serializeToJson() const {
    QJsonObject result = Unit::serializeToJson().toObject();
    QJsonArray nodes;

    for (auto node : m_nodes) {
        nodes.append(node->serializeToJson());
    }

    result["nodes"] = nodes;
    return result;
}

}
