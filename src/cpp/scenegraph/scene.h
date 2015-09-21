#pragma once
#include <QtCore>

class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(QObject *parent = 0);
};
