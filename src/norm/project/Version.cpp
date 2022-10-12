#include "Version.h"

namespace Norm {

Version::Version() {

}

void Version::setVersion(const QVersionNumber& version) {
    m_version = version;
}

QVersionNumber Version::version() const {
    return m_version;
}

Version::Kind Version::kind() const {
    return m_kind;
}

void Version::setKind(Kind kind) {
    m_kind = kind;
}

void Version::serialize(QDataStream& stream) const {
    Token::serialize(stream);

    stream << (quint8)m_kind;

    stream << (quint8)m_version.majorVersion();
    stream << (quint8)m_version.minorVersion();
    stream << (quint8)m_version.microVersion();
}

void Version::deserialize(QDataStream& stream) {
    Token::deserialize(stream);

    quint8 kind;

    quint8 majour;
    quint8 minor;
    quint8 micro;

    stream >> kind >> majour >> minor >> micro;

    m_kind = Kind(kind);
    m_version = QVersionNumber(majour, minor, micro);
}

}
