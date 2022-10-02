#pragma once
#include "project/Node.h"
#include <QJsonObject>

namespace Unit {

class Unit : public Node {
public:
    enum class Kind {
        Project,
        Module,
        Interface,
        Function,
        Flow,
        Parameter,
        Expression,
        Condition,
        Loop,
        Operator,
        Constant,
        Variable,
        Structure,
        Field,
        Custom
    };

    Unit(Node* parent = nullptr);

    virtual Kind kind() const = 0;

    QString comment() const;
    void setComment(const QString& comment);

    QJsonObject toJson() const;

    QByteArray toBinary() const;
    void fromBinary(const QByteArray& binary);

protected:
    virtual QJsonObject toJsonUnit() const = 0;

    virtual QByteArray toBinaryUnit() const = 0;
    virtual void fromBinaryUnit(const QByteArray& binary) = 0;

private:
    QString m_comment;
};

}
