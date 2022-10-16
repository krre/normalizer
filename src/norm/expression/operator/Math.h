#pragma once
#include "norm/expression/Expression.h"

namespace Norm {

class Math : public Expression {
public:
    enum class Operation : quint8 {
        Addition,
        Subtraction,
        Multiplication,
        Division
    };

    Math();
    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    Operation operation() const;
    void setOperation(Operation operation);

private:
    Operation m_operation;
};

}
