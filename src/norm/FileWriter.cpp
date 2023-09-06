#include "FileWriter.h"
#include "Token.h"
#include "core/Constants.h"
#include "core/Exception.h"
#include <QFile>
#include <QVersionNumber>

namespace Norm {

FileWriter::FileWriter() {

}

void FileWriter::write(Token* root, const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QFile::WriteOnly)) {
        throw Exception("Failed to write file '{}'", filePath);
    }

    QDataStream ds(&file);
    ds.writeRawData(Const::Norm::Magic, QString(Const::Norm::Magic).length());

    QVersionNumber version = QVersionNumber::fromString(Const::Norm::Version);
    ds << static_cast<quint8>(version.majorVersion());
    ds << static_cast<quint8>(version.minorVersion());

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
