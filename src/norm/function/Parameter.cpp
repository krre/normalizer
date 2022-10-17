#include "Parameter.h"
#include "core/Constants.h"

namespace Norm {

Parameter::Parameter() {

}

Code Parameter::code() const {
    return Const::Norm::Token::Parameter;
}

void Parameter::serialize(QDataStream& stream) const {
    Token::serialize(stream);
    FunctionId::serialize(stream);
    Name::serialize(stream);
    TypeId::serialize(stream);
}

void Parameter::deserialize(QDataStream& stream) {
    Token::deserialize(stream);
    FunctionId::deserialize(stream);
    Name::deserialize(stream);
    TypeId::deserialize(stream);
}

}
