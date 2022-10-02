#include "Expression.h"
#include <QJsonValue>

namespace Expression {

Expression::Expression(Node* parent) : Node(parent) {

}

QJsonValue Expression::serializeToJson() const {
    return Node::serializeToJson();
}

}
