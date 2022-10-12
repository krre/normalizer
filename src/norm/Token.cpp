#include "Token.h"
#include <QDataStream>

namespace Norm {

Token::Token() {

}

Token::Id Token::id() const {
    return m_id;
}

void Token::setId(Id id) {
    m_id = id;
}

void Token::serialize(QDataStream& stream) const {
    stream << m_id;
}

void Token::deserialize(QDataStream& stream) {
    stream >> m_id;
}

}
