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

    Id moduleId() const;
    void setModuleId(Id parentId);

private:
    Id m_moduleId = 0;
};

}
