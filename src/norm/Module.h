#pragma once
#include "Token.h"
#include <QScopedPointer>

namespace Norm {

class Name;

class Module : public Token {
public:
    Module();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    Module* parent() const;
    void setParent(Module* parent);

private:
    Module* m_parent = nullptr;
};

}
