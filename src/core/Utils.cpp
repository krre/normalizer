#include "Utils.h"
#include <QCryptographicHash>

Utils::Utils() {}

QString Utils::sha256(const QString& data) {
    QByteArray hash = QCryptographicHash::hash(data.toUtf8(), QCryptographicHash::Sha256);
    return QString(hash.toHex());
}

QString Utils::normHome() {
    return qEnvironmentVariable("NORM_HOME");
}
