#pragma once
#include <QtGlobal>

namespace Norm {

class Token {
public:
    enum class Type : quint8 {
        Header = 00
    };

    Token();
    virtual Type type() const;

    virtual void serialize(QDataStream& stream) const;
    virtual void deserialize(QDataStream& stream);

private:
    Type m_type;
};

}
