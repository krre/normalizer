#pragma once
#include <QtCore>
#include <QtSql>

class SproutDb: public QObject
{
    Q_OBJECT

public:
    SproutDb();
    ~SproutDb();
    Q_INVOKABLE void open(const QString& path);
    Q_INVOKABLE void close();
    Q_INVOKABLE QVariantList readRecords(const QString& sql);
    Q_INVOKABLE void insertRecord(const QString& sql);
    Q_INVOKABLE void updateRecord(const QString &sql);
    Q_INVOKABLE void deleteRecord(const QString &sql);
private:
    QSqlDatabase db;
};
