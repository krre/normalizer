#include "Function.h"

namespace Unit {

Function::Function() {

}

Unit::Type Function::type() const {
    return Type::Function;
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

}
