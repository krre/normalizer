#include "utils.h"

QString Utils::urlToPath(QUrl url)
{
    return url.toLocalFile();
}

QString Utils::urlToFileName(QUrl url)
{
    return url.fileName().replace(".sprout", "");
}

bool Utils::isFileExists(const QString &filePath)
{
    QFileInfo checkFile(filePath);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

