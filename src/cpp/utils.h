#pragma once
#include <QtCore>

class Utils : public QObject
{

public:
    explicit Utils(QObject* parent = 0) { Q_UNUSED(parent) }
    static bool isFileExists(const QString& filePath);
    static void removeFile(const QString& path);
};
