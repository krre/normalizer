#pragma once
#include "Token.h"
#include "Sign.h"

namespace Norm {

class Project : public Token {
public:
    enum class Template {
        Binary,
        Library
    };

    Project(const QString& name, Template projectTemplate);
    Project() = default;

    QString sign() const override { return Sign::Project; }

    void setName(const QString& name);
    QString name() const;

    Template projectTemplate() const;

protected:
    void getSerializedProperties(SerializedProperties& properties) const override;
    void setParsedProperties(ParsedProperties& properties) override;

private:
    QString m_name;
    Template m_projectTemplate;
};

}
