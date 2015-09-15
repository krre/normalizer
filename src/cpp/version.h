#pragma once

#include <QObject>

#define MAJOR 0
#define MINOR 1
#define PATCH 0

class Version : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString full READ full CONSTANT)

public:
    explicit Version() {}
    Q_INVOKABLE static unsigned int major() { return MAJOR; }
    Q_INVOKABLE static unsigned int minor() { return MINOR; }
    Q_INVOKABLE static unsigned int patch() { return PATCH; }
    Q_INVOKABLE static QString full() { return QString("%1.%2.%3").arg(MAJOR).arg(MINOR).arg(PATCH); }
};
