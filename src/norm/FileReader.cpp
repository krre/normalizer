#include "FileReader.h"
#include "Token.h"
#include "Project.h"
#include "core/Constants.h"
#include "core/Exception.h"
#include <QFile>
#include <QHash>
#include <QVersionNumber>

namespace Norm {

FileReader::FileReader() {

}

Token* FileReader::read(const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly)) {
        throw Exception("Failed to read file '{}'", filePath);
    }

    QDataStream ds(&file);

    int magicSize = QString(Const::Norm::Magic).length();
    char magic[magicSize];
    ds.readRawData(magic, magicSize);

    if (QString::fromLatin1(magic, magicSize) != Const::Norm::Magic) {
        throw Exception("Invalid file format");
    }

    quint8 majour;
    ds >> majour;

    quint8 minor;
    ds >> minor;

    QVersionNumber version(majour, minor);

    if (version > QVersionNumber::fromString(Const::Norm::Version)) {
        throw Exception("Version Norm file greater than supported");
    }

    QHash<TokenId, Token*> tokens;
    Token* rootToken = nullptr;

    while (!file.atEnd()) {
        QDataStream ds(&file);

        TokenSize size;
        ds >> size;

        TokenType type;
        ds >> type;

        QByteArray ba = file.read(size - sizeof(TokenType));
        Token* token = nullptr;

        if (type == TokenType::Project) {
            token = new Project;
        } else {
            throw Exception("Token not found");
        }

        token->parse(ba);
        tokens[token->id()] = token;

        if (!rootToken) {
            rootToken = token;
        }
    }

    return rootToken;
}

}
