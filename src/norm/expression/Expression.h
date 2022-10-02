#pragma once
#include "project/Node.h"
#include <QList>

namespace Type {
    class Type;
}

namespace Expression {

class Expression;

using Expressions = QList<Expression*>;

class Expression : public Node {
public:
    Expression(Node* parent = nullptr);
    virtual Type::Type* value() { return nullptr; }

    QJsonValue serializeToJson() const override;
};

}
