#include "Version.h"

namespace Norm {

Version::Version() {

}

Token::Type Version::type() const {
    return Token::Type::Version;
}

void Version::setVersion(const QVersionNumber& version) {
    m_version = version;
}

QVersionNumber Version::version() const {
    return m_version;
}

void Version::serialize(QDataStream& stream) const {
    Token::serialize(stream);

    stream << (quint8)m_version.majorVersion();
    stream << (quint8)m_version.minorVersion();
    stream << (quint8)m_version.microVersion();
}

void Version::deserialize(QDataStream& stream) {
    Token::deserialize(stream);

    quint8 majour;
    quint8 minor;
    quint8 micro;

    stream >> majour >> minor >> micro;
    m_version = QVersionNumber(majour, minor, micro);
}

}
