#include "Token.h"
#include <QDataStream>

namespace Norm {

Token::Token() {

}

Id Token::id() const {
    return m_id;
}

void Token::setId(Id id) {
    m_id = id;
}

Id Token::parentId() const {
    return m_parentId;
}

void Token::setParentId(Id parentId) {
    m_parentId = parentId;
}

void Token::serialize(QDataStream& stream) const {
    stream << quint8(type()) << m_id << m_parentId;
}

void Token::deserialize(QDataStream& stream) {
    stream >> m_id >> m_parentId;
}

}
