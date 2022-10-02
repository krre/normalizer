#pragma once
#include "Unit.h"
#include "helper/Name.h"
#include <QSharedPointer>

namespace Unit {

class Parameter;
using Parameters = QList<QSharedPointer<Parameter>>;

class Function : public Unit, public Helper::Name {
public:
    Function(Node* parent = nullptr);
    Kind kind() const override;

    const Parameters& parameters() const;
    void setParameters(const Parameters& parameters);

protected:
    QJsonObject toJsonUnit() const override;

    QByteArray toBinaryUnit() const override;
    void fromBinaryUnit(const QByteArray& binary) override;

private:
    Parameters m_parameters;
};

}
