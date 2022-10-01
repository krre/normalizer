#include "Type.h"

namespace Type {

Type::Type() {

}

Type::Id Type::id() const {
    return m_id;
}

QString Type::name() const {
    return m_name;
}

void Type::setName(const QString& name) {
    m_name = name;
}

}
