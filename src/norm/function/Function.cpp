#include "Function.h"
#include "norm/Name.h"
#include "core/Constants.h"

namespace Norm {

Function::Function() {
}

Code Function::code() const {
    return Const::Norm::Token::Version;
}

void Function::serialize(QDataStream& stream) const {
    Token::serialize(stream);

    stream << name()->id();
}

void Function::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
}

}
