#include "Token.h"
#include <QDataStream>

Token::Token() {

}

Token::Type Token::type() const {
    return m_type;
}

void Token::serialize(QDataStream& stream) const {
    stream << quint8(type());
}

void Token::deserialize(QDataStream& stream) {
    stream >> m_type;
}
