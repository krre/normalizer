#include "utils.h"

bool Utils::isFileExists(const QString& filePath)
{
    QFileInfo checkFile(filePath);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}

void Utils::removeFile(const QString& path)
{
    QDir dir;
    dir.remove(path);
}
