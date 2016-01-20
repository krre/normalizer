#include "core.h"

QString Core::urlToPath(QUrl url)
{
    return url.toLocalFile();
}

QString Core::urlToFileName(QUrl url)
{
    return url.fileName().replace(".sprout", "");
}

bool Core::isFileExists(const QString& filePath)
{
    QFileInfo checkFile(filePath);
    // check if file exists and if yes: Is it really a file and no directory?
    return checkFile.exists() && checkFile.isFile();
}

void Core::removeFile(const QString& path)
{
    QDir dir;
    dir.remove(path);
}

PositionAttitudeTransform* Core::findUnit(const PositionAttitudeTransform* parentUnit, const QString& nameUnit) const
{
    return parentUnit->findChild<PositionAttitudeTransform*>(nameUnit);
}
