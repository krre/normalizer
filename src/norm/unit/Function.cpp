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

QJsonValue Function::serializeToJson() const {
    QJsonObject result = Unit::serializeToJson().toObject();
    result["name"] = name();

    if (!m_parameters.isEmpty()) {
        QJsonArray parameters;

        for (auto& parameter : m_parameters) {
            parameters.append(parameter->serializeToJson());
        }

        result["parameters"] = parameters;
    }

    return result;
}

}
