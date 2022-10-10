#pragma once
#include <QtGlobal>
#include <QList>

namespace Norm {

class Token;

using Id = quint16;
using IdList = QList<Id>;

class Token {
public:
    enum class Type : quint8 {
        Porject = 00,
        Version = 01,
        Name    = 02,
    };

    Token();
    virtual Type type() const = 0;

    Id id() const;
    void setId(Id id);

    Id parentId() const;
    void setParentId(Id parentId);

    virtual void serialize(QDataStream& stream) const;
    virtual void deserialize(QDataStream& stream);

private:
    Id m_id = -1;
    Id m_parentId = -1;
};

}
