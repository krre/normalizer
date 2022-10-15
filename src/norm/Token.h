#pragma once
#include <QtGlobal>
#include <QList>
#include "core/CommonTypes.h"

namespace Norm {

class Token {
public:
    Token();

    Code virtual code() const = 0;

    Id id() const;
    void setId(Id id);

    virtual void serialize(QDataStream& stream) const;
    virtual void deserialize(QDataStream& stream);

private:
    Id m_id = -1;
};

}
