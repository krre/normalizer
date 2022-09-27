#include "Function.h"

Function::Function() {

}

Unit::Type Function::type() const {
    return Type::Function;
}

QString Function::name() const {
    return QString();
}

QJsonObject Function::toJsonUnit() const {
    QJsonObject result;
    return result;
}

QByteArray Function::toBinaryUnit() const {
    QByteArray result;
    return result;
}

void Function::fromBinaryUnit(const QByteArray& binary) {

}
