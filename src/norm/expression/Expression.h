#pragma once

namespace Type {
    class Type;
}

namespace Expression {

class Expression {
public:
    Expression();
    virtual Type::Type* value() { return nullptr; }

private:

};

}
