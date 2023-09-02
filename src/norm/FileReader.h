#pragma once
#include <QString>

namespace Norm {

class Token;

class FileReader {
public:
    FileReader();
    Token* read(const QString& filePath);
};

}
