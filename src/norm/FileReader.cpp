#include "FileReader.h"
#include "Token.h"
#include "core/Exception.h"
#include <QFile>

namespace Norm {

FileReader::FileReader() {

}

Token* FileReader::read(const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly)) {
        throw Exception("Failed to read file '{}'", filePath);
    }

    QDataStream stream(&file);

    while (!stream.atEnd()) {
        Norm::TokenType type;
        stream >> type;

        qDebug() << "type" << int(type);
    }

    return nullptr;
}

}
