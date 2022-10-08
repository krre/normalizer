#include "Header.h"
#include <QByteArray>
#include <QDataStream>

Header::Header() {

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

QByteArray Header::serialize() const {
    QByteArray result;

    QDataStream stream(result);
    stream << (quint8)m_version.majorVersion();
    stream << (quint8)m_version.minorVersion();
    stream << (quint8)m_version.microVersion();

    return result;
}

void Header::deserialize(const QByteArray& data) {
    QDataStream stream(data);

    int majour;
    int minor;
    int micro;

    stream >> majour >> minor >> micro;
    m_version = QVersionNumber(majour, minor, micro);
}
