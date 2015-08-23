#include "utils.h"

QString Utils::urlToPath(QUrl url)
{
    return url.toLocalFile();
}

QString Utils::urlToFileName(QUrl url)
{
    return url.fileName().replace(".sprout", "");
}

QVariant Utils::loadSproutFile(const QString &filePath)
{
    QFile file(filePath);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QByteArray byteArray;
    while (!file.atEnd())
        byteArray.append(file.readLine());

    return byteArray;
}

void Utils::saveSproutFile(const QString filePath, const QVariant &fileData)
{
    QFile file(filePath);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&file);
    out << fileData.toString();
    file.close();
}
