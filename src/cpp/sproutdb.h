#pragma once
#include <QtCore>
#include <QtSql>

class SproutDb: public QObject
{
    Q_OBJECT

public:
    SproutDb();
    ~SproutDb();
    Q_INVOKABLE void open(const QString &path);
    Q_INVOKABLE void readRecord();
    Q_INVOKABLE void insertRecord();
    Q_INVOKABLE void updateRecord();
    Q_INVOKABLE void deleteRecord();
private:
    QSqlDatabase db;
};
