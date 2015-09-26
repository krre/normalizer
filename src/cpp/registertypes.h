#pragma once
#include <QObject>

class RegisterTypes : public QObject
{
    Q_OBJECT
public:
    explicit RegisterTypes(QObject *parent = 0);
    static void run();
};
