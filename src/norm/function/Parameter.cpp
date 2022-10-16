#include "Parameter.h"
#include "core/Constants.h"

namespace Norm {

Parameter::Parameter() {

}

Code Parameter::code() const {
    return Const::Norm::Token::Parameter;
}

void Parameter::serialize(QDataStream& stream) const {
    NameId::serialize(stream);
    TypeId::serialize(stream);
}

void Parameter::deserialize(QDataStream& stream) {
    NameId::deserialize(stream);
    TypeId::deserialize(stream);
}

}
