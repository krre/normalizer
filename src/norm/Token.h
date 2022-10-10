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
        Header = 03,
    };

    Token();
    virtual Type type() const;

    Id id() const;
    void setId(Id id);

    Id parentId() const;
    void setParentId(Id parentId);

    virtual void serialize(QDataStream& stream) const;
    virtual void deserialize(QDataStream& stream);

private:
    Type m_type;
    Id m_id = -1;
    Id m_parentId = -1;
};

}
