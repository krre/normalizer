#pragma once

class QDataStream;

namespace Norm::Helper {

class Helper {
public:
    Helper();

    virtual void serialize(QDataStream& stream) const = 0;
    virtual void deserialize(QDataStream& stream) = 0;
};

}
