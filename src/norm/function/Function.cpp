#include "Function.h"
#include "core/Constants.h"

namespace Norm {

Function::Function() {
}

Code Function::code() const {
    return Const::Norm::Token::Function;
}

void Function::serialize(QDataStream& stream) const {
    Token::serialize(stream);
    Name::serialize(stream);
    ModuleId::serialize(stream);
}

void Function::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
    Name::deserialize(stream);
    ModuleId::deserialize(stream);
}

}
