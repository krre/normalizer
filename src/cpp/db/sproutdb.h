#pragma once
#include <QtCore>
#include <QtSql>

class SproutDb : public QObject
{
    Q_OBJECT
public:
    SproutDb();
    Q_INVOKABLE QString create(const QString& path);

private:
    QSqlError initTables();
    QSqlError initRecords();
    QSqlDatabase db;

};
