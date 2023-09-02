#include "Token.h"
#include <QDataStream>

namespace Norm {

//QByteArray Token::serialize() const {
//    QByteArray result;
//    return result;
//    SerializedProperties properties;
//    getSerializedProperties(properties);

//    QString result = sign();

//    for (const auto& property : properties.properties) {
//        result += " " + property.first + " " + property.second.toString();
//    }

//    return result;
//}

//void Token::parse(const QString& line) {
//    ParsedProperties properties;
//    properties.sign = sign();

//    QTextStream stream(line.toUtf8());

//    while (!stream.atEnd()) {
//        QString name;
//        stream >> name;

//        QString value;
//        stream >> value;

//        properties.properties[name] = value;
//    }

//    setParsedProperties(properties);
//}

}
