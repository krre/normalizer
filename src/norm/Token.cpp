#include "Token.h"
#include <QDataStream>

namespace Norm {

Token::Token() {

}

Token::Type Token::type() const {
    return m_type;
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

void Token::setChildren(const IdList& children) {
    m_children = children;
}

const IdList& Token::children() const {
    return m_children;
}

void Token::addChild(Id childId) {
    m_children.append(childId);
}

void Token::removeChild(Id childId) {
    m_children.removeOne(childId);
}

void Token::serialize(QDataStream& stream) const {
    stream << quint8(type());
}

void Token::deserialize(QDataStream& stream) {
    stream >> m_type;
}

}
