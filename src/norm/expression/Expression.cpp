#include "Expression.h"

namespace Norm {

Expression::Expression() {

}

void Expression::serialize(QDataStream& stream) const {
    Token::serialize(stream);
    FunctionId::serialize(stream);
}

void Expression::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
    FunctionId::deserialize(stream);
}

}
