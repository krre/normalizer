#pragma once
#include <QtGlobal>
#include <QList>

namespace Norm {

class Token {
public:
    using Id = quint16;

    Token();

    Id id() const;
    void setId(Id id);

    virtual void serialize(QDataStream& stream) const;
    virtual void deserialize(QDataStream& stream);

private:
    Id m_id = -1;
};

}
