#pragma once
#include <QtCore>
#include <QtSql>

class SproutDb: public QObject
{
    Q_OBJECT

public:
    SproutDb();
    ~SproutDb();
    Q_INVOKABLE bool create(const QString &path);
    Q_INVOKABLE void open(const QString &path);
private:
    void initDb();
    QSqlDatabase db;
};
