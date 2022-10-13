#include "Name.h"

namespace Norm::Helper {

Name::Name() {

}

Norm::Name* Name::name() const {
    return m_name;
}

void Name::setName(Norm::Name* name) {
    m_name = name;
}

}
