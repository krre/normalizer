#include "FileReader.h"
#include "Token.h"
#include "Project.h"
#include "core/Exception.h"
#include <QFile>
#include <QHash>

namespace Norm {

FileReader::FileReader() {

}

Token* FileReader::read(const QString& filePath) {
    QFile file(filePath);

    if (!file.open(QFile::ReadOnly)) {
        throw Exception("Failed to read file '{}'", filePath);
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
