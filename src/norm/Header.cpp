#include "Header.h"
#include <QDataStream>

namespace Norm {

Header::Header() {

}

Header::~Header() {

}

Token::Type Header::type() const {
    return Type::Header;
}

void Header::setVersion(const QVersionNumber& version) {
    m_version = version;
}

QVersionNumber Header::version() const {
    return m_version;
}

void Header::serialize(QDataStream& stream) const {
    Token::serialize(stream);

    stream << (quint8)m_version.majorVersion();
    stream << (quint8)m_version.minorVersion();
    stream << (quint8)m_version.microVersion();
}

void Header::deserialize(QDataStream& stream) {
    Token::deserialize(stream);

    quint8 majour;
    quint8 minor;
    quint8 micro;

    stream >> majour >> minor >> micro;
    m_version = QVersionNumber(majour, minor, micro);
}

}

