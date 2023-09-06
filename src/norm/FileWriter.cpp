#include "FileWriter.h"
#include "Token.h"
#include "core/Exception.h"
#include <QFile>

namespace Norm {

FileWriter::FileWriter() {

}

void FileWriter::write(Token* root, const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QFile::WriteOnly)) {
        throw Exception("Failed to write file '{}'", filePath);
    }

    file.write(serializeToken(root));
}

QByteArray FileWriter::serializeToken(Token* token) {
    QByteArray result = token->serialize();

    QByteArray sizeBa;
    QDataStream ds(&sizeBa, QIODeviceBase::WriteOnly);
    TokenSize size = result.size();
    ds << size;

    result.prepend(sizeBa);

    for (auto child : token->children()) {
        result += serializeToken(static_cast<Token*>(child));
    }

    return result;
}

}
