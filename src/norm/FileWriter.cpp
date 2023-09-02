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

    file.write(root->serialize());
}

}
