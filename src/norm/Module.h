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

    Name* name() const;
    void setName(Name* name);

    Module* parent() const;
    void setParent(Module* parent);

private:
    QScopedPointer<Name> m_name;
    Module* m_parent = nullptr;
};

}
