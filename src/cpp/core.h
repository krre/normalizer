#pragma once
#include <QtCore>
#include <osg/positionattitudetransform.h>

class Core : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString buildDate READ buildDate CONSTANT)
    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)
    Q_PROPERTY(QString homePath READ homePath CONSTANT)

public:
    QString buildDate() { return QString(__DATE__); }
    QString qtVersion() { return QT_VERSION_STR; }
    Q_INVOKABLE QString urlToPath(QUrl url);
    Q_INVOKABLE QString urlToFileName(QUrl url);
    QString homePath() { return QStandardPaths::writableLocation(QStandardPaths::HomeLocation); }
    Q_INVOKABLE static bool isFileExists(const QString& filePath);
    Q_INVOKABLE static void removeFile(const QString& path);
    Q_INVOKABLE PositionAttitudeTransform* findUnit(const PositionAttitudeTransform* parentUnit, const QString& nameUnit) const;
};
