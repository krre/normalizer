#pragma once
#include "Unit.h"

namespace Unit {

class Flow : public Unit {
public:
    Flow(Node* node);
    Kind kind() const override;

    void append(Node* node);

protected:
    QJsonObject toJsonUnit() const override;

    QByteArray toBinaryUnit() const override;
    void fromBinaryUnit(const QByteArray& binary) override;

private:
    Nodes m_nodes;
};

}
