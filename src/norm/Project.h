#pragma once
#include "Token.h"
#include "TokenType.h"

namespace Norm {

class Project : public Token {
public:
    enum class Template {
        Binary,
        Library
    };

    Project(const QString& name, Template projectTemplate);
    Project() = default;

    TokenType type() const override { return TokenType::Project; }

    void setName(const QString& name);
    QString name() const;

    Template projectTemplate() const;

protected:
    void getSerializedProperties(QDataStream& stream) const override;
    void setParsedProperties(const QDataStream& stream) override;

private:
    QString m_name;
    Template m_projectTemplate;
};

}
