#pragma once
#include "project/Node.h"
#include <QVector>

namespace Type {
    class Type;
}

namespace Expression {

class Expression;

using Expressions = QVector<Expression*>;

class Expression : public Node {
public:
    Expression();
    virtual Type::Type* value() { return nullptr; }

private:

};

}
