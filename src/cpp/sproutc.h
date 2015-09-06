#pragma once
#include <QtCore>

#include <QObject>

class SproutC : public QObject
{
    Q_OBJECT
public:
    explicit SproutC(QObject *parent = 0);
    Q_INVOKABLE QVariantMap version();

signals:

public slots:
};

