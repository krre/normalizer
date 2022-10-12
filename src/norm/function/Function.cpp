#include "Function.h"

namespace Norm {

Function::Function() {
}

void Function::serialize(QDataStream& stream) const {
    Token::serialize(stream);
}

void Function::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
}

}
