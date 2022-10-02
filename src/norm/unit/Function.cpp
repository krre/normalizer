#include "Function.h"
#include "Parameter.h"
#include "project/Node.h"
#include <QJsonArray>

namespace Unit {

Function::Function(Node* parent) : Unit(parent) {

}

Unit::Kind Function::kind() const {
    return Kind::Function;
}

const Parameters& Function::parameters() const {
    return m_parameters;
}

void Function::setParameters(const Parameters& parameters) {
    m_parameters = parameters;
}

QJsonObject Function::toJsonUnit() const {
    QJsonObject result;
    result["name"] = name();

    QJsonArray parameters;

    for (auto& parameter : m_parameters) {
        parameters.append(parameter->toJson());
    }

    result["parameters"] = parameters;
    return result;
}

QByteArray Function::toBinaryUnit() const {
    QByteArray result;
    return result;
}

void Function::fromBinaryUnit(const QByteArray& binary) {

}

}
