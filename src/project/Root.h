#pragma once
#include "Node.h"

class Root : public Node {
public:
    Root();

    QByteArray serializeToBinary() const override;
    QJsonValue serializeToJson() const override;
};
