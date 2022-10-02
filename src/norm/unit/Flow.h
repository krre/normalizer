#pragma once
#include "Unit.h"

namespace Unit {

class Flow : public Unit {
public:
    Flow(Node* node);
    Kind kind() const override;

    void append(Node* node);

    QJsonValue serializeToJson() const override;

private:
    Nodes m_nodes;
};

}
