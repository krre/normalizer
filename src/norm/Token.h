#pragma once
#include "core/Exception.h"
#include <QVariant>

namespace Norm {

class Token {
public:
    Token();

    virtual QString sign() const = 0;

    QString serialize() const;
    void parse(const QString& line);

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
                throw Exception(QString("Property '%1' not found in token '%2'").arg(name, sign));
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
