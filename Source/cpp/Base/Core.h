#pragma once
#include <QObject>

class Core : public QObject {
    Q_OBJECT
    Q_PROPERTY(QString buildDate READ buildDate CONSTANT)
    Q_PROPERTY(QString qtVersion READ qtVersion CONSTANT)

public:
    QString buildDate() { return QString(__DATE__); }
    QString qtVersion() { return QT_VERSION_STR; }
};
