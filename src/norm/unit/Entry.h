#pragma once
#include "Function.h"

namespace Unit {

class Entry : public Function {
public:
    Entry(Node* parent = nullptr);

    QJsonValue serializeToJson() const override;
};

}
