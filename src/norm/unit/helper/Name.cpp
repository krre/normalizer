#include "Name.h"

namespace Unit::Helper {

Name::Name() {

}

QString Name::name() const {
    return m_name;
}

void Name::setName(const QString& name) {
    m_name = name;
}

}
