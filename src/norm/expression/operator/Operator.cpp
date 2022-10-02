#include "Operator.h"
#include <QJsonValue>

namespace Expression::Operator {

Operator::Operator(Node* parent) : Expression(parent) {

}

QJsonValue Operator::serializeToJson() const {
    return Node::serializeToJson();
}

}
