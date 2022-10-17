#pragma once
#include "norm/expression/Expression.h"
#include "core/Constants.h"

namespace Norm {

template <typename T>
class Literal : public Expression {
public:
    Literal() {}

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

class StringLiteral : public Literal<QString> {
public:
    StringLiteral() {}
    Code code() const override { return Const::Norm::Token::StringLiteral; }
};

class NumberLiteral : public Literal<double> {
public:
    NumberLiteral() {}
    Code code() const override { return Const::Norm::Token::NumberLiteral; }
};

class BooleanLiteral : public Literal<bool> {
public:
    BooleanLiteral() {}
    Code code() const override { return Const::Norm::Token::BooleanLiteral; }
};

}
