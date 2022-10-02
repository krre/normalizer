#include "Unit.h"

namespace Unit {

Unit::Unit(Node* parent) : Node(parent) {

}

QString Unit::comment() const {
    return m_comment;
}

void Unit::setComment(const QString& comment) {
    m_comment = comment;
}

QJsonValue Unit::serializeToJson() const {
    QJsonObject result = Node::serializeToJson().toObject();
    result["kind"] = qint64(kind());

    if (!m_comment.isEmpty()) {
        result["comment"] = m_comment;
    }

    return result;
}

}
