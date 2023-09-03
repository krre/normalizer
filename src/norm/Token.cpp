#include "Token.h"
#include <QDataStream>

namespace Norm {

void Token::setId(TokenId id) {
    m_id = id;
}

TokenId Token::id() const {
    return m_id;
}

QByteArray Token::serialize() const {
    QByteArray result;
    QDataStream stream(&result, QIODeviceBase::WriteOnly);

    stream << type() << m_id;
    getSerializedProperties(stream);

    return result;
}

void Token::parse(const QByteArray& data) {
    QDataStream stream(data);

    stream >> m_id;
    setParsedProperties(stream);
}

}
