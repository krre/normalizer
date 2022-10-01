#include "Unit.h"

namespace Unit {

Unit::Unit() {

}

Unit::Id Unit::id() const {
    return m_id;
}

void Unit::setId(Id id) {
    m_id = id;
}

QString Unit::comment() const {
    return m_comment;
}

void Unit::setComment(const QString& comment) {
    m_comment = comment;
}

QJsonObject Unit::toJson() const {
    QJsonObject result = toJsonUnit();
    result["id"] = m_id;
    result["kind"] = qint64(kind());

    if (!m_comment.isEmpty()) {
        result["comment"] = m_comment;
    }

    return result;
}

QByteArray Unit::toBinary() const {
    QByteArray result = toBinaryUnit();
    return result;
}

void Unit::fromBinary(const QByteArray& binary) {

}

}
