#pragma once
#include "norm/Token.h"
#include <QVersionNumber>

namespace Norm {

class Version : public Token {
public:
    enum class Kind : quint8 {
        Project,
        Norm
    };

    Version();

    Code code() const override;

    void setVersion(const QVersionNumber& version);
    QVersionNumber version() const;

    Kind kind() const;
    void setKind(Kind kind);

    void serialize(QDataStream& stream) const override;
    void deserialize(QDataStream& stream) override;

private:
    QVersionNumber m_version;
    Kind m_kind;
};

}
