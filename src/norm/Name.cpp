#include "Name.h"
#include <QDataStream>

namespace Norm {

Name::Name() {

}

Token::Type Name::type() const {
    return Token::Type::Name;
}

void Name::serialize(QDataStream& stream) const {
    stream << m_name;
}

void Name::deserialize(QDataStream& stream) {
    stream >> m_name;
}

QString Name::name() const {
    return m_name;
}

void Name::setName(const QString& name) {
    m_name = name;
}

}
