#pragma once
#include <QString>

namespace Norm {

class Token;

class FileWriter {
public:
    FileWriter();
    void write(Token* root, const QString& filePath);

private:
    QByteArray serializeToken(Token* token);
};

}
