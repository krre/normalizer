#pragma once
#include "norm/expression/Expression.h"
#include "core/Constants.h"

namespace Norm {

template <typename T, Code C>
class Literal : public Expression {
public:
    Literal();

    Code code() const override {
        return C;
    }

    void serialize(QDataStream& stream) const override {
        stream << m_literal;
    }

    void deserialize(QDataStream& stream) override {
        stream >> m_literal;
    }

    void setLiteral(const T& literal) {
        m_literal = literal;
    }

    const T& literal() const {
        return m_literal;
    }

private:
    T m_literal;
};

class StringLiteral : public Literal<QString, Const::Norm::Token::StringLiteral> {

};

class NumberLiteral : public Literal<double, Const::Norm::Token::NumberLiteral> {

};

class BooleanLiteral : public Literal<bool, Const::Norm::Token::BooleanLiteral> {

};

}
