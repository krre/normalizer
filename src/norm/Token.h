#pragma once
#include "TokenType.h"
#include "core/Exception.h"
#include <QVariant>

namespace Norm {

class Token {
public:
    virtual TokenType type() const = 0;

    QByteArray serialize() const;

    void parse(const QByteArray& data);

protected:
    struct SerializedProperties {
        void append(const QString& name, const QVariant& value) {
            properties.append({ name, value });
        }

        QList<QPair<QString, QVariant>> properties;
    };

    struct ParsedProperties {
        QVariant value(const QString& name) const {
            if (!properties.contains(name)) {
                throw Exception("Property '{}' not found in token '{}'", name, sign);
            }

            return properties.value(name);
        }

        QVariantHash properties;
        QString sign;
    };

    virtual void getSerializedProperties(SerializedProperties& properties) const = 0;
    virtual void setParsedProperties(ParsedProperties& properties) = 0;
};

}
