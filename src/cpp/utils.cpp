#include "utils.h"

QString Utils::urlToPath(QUrl url)
{
    return url.toLocalFile();
}

QString Utils::urlToFileName(QUrl url)
{
    return url.fileName().replace(".sprout", "");
}

bool Utils::isFileExists(const QString& filePath)
{
    QFileInfo checkFile(filePath);
    // check if file exists and if yes: Is it really a file and no directory?
    return checkFile.exists() && checkFile.isFile();
}

void Utils::removeFile(const QString& path)
{
    QDir dir;
    dir.remove(path);
}

PositionAttitudeTransform* Utils::findUnit(const PositionAttitudeTransform* parentUnit, const QString& nameUnit) const
{
    return parentUnit->findChild<PositionAttitudeTransform*>(nameUnit);
}
