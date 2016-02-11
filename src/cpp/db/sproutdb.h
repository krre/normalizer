#pragma once
#include <QtCore>
#include <QtSql>

class SproutDb : public QObject
{
    Q_OBJECT
public:
    SproutDb();
    Q_INVOKABLE bool create(const QString& path);
};
