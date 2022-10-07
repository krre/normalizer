#include "Unit.h"

namespace Unit {

Unit::Unit(Node* parent) : Node(parent) {

}

QString Unit::comment() const {
    return m_comment;
}

void Unit::setComment(const QString& comment) {
    m_comment = comment;
}

}
