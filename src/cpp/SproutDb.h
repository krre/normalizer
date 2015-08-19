#pragma once
#include <QtCore>
#include <QtSql>

class SproutDb: public QObject
{
    Q_OBJECT

public:
    SproutDb();
    ~SproutDb();
    Q_INVOKABLE void create(const QString &path);
private:
    QSqlDatabase db;
};
