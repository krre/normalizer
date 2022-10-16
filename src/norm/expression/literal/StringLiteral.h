#pragma once
#include "norm/expression/Expression.h"
#include <QString>

namespace Norm {

class StringLiteral : public Expression {
public:
    StringLiteral();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    void setLiteral(const QString& literal);
    const QString& literal() const;

private:
    QString m_literal;
};

}
