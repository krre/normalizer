#include "Parameter.h"

namespace Norm {

Parameter::Parameter() {

}

Type::Type* Parameter::type() const {
    return m_type;
}

void Parameter::setType(Type::Type* type) {
    m_type = type;
}

}
