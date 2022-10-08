#pragma once
#include <QtGlobal>

class Token {
public:
    enum class Type : quint8 {
        Header = 00
    };

    Token();
    virtual Type type() const = 0;

    virtual void serialize(QDataStream& stream) const = 0;
    virtual void deserialize(QDataStream& stream) = 0;
};
