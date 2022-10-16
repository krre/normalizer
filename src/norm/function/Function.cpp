#include "Function.h"
#include "norm/Name.h"
#include "core/Constants.h"

namespace Norm {

Function::Function() {
}

Code Function::code() const {
    return Const::Norm::Token::Function;
}

void Function::serialize(QDataStream& stream) const {
    Token::serialize(stream);
    NameId::serialize(stream);
    ModuleId::serialize(stream);
}

void Function::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
    NameId::deserialize(stream);
    ModuleId::deserialize(stream);
}

void Function::addParameter(Parameter* parameter) {
    parameters.append(parameter);
}

void Function::removeParameter(Parameter* parameter) {
    parameters.removeOne(parameter);
}

}
