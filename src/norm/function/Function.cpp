#include "Function.h"
#include "core/Constants.h"

namespace Norm {

Function::Function() {
}

Code Function::code() const {
    return Const::Norm::Token::Version;
}

void Function::serialize(QDataStream& stream) const {
    Token::serialize(stream);
}

void Function::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
}

}
