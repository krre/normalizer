#pragma once
#include "norm/Token.h"

namespace Norm {

class Project : public Token {
public:
    enum class Target {
        Application,
        Library
    };

    Project();
    virtual ~Project();

    Code code() const override;

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

    Target target() const;
    void setTarget(Target target);

private:
    Target m_target;
};

}
