#pragma once
#include <QObject>
#include <QSqlError>
#include <QSqlDatabase>
#include <QVariantList>

class SproutDb : public QObject {
    Q_OBJECT
public:
    SproutDb();
    Q_INVOKABLE QString create(const QString& path);
    Q_INVOKABLE QString open(const QString& path);
    Q_INVOKABLE void close();
    Q_INVOKABLE QVariantList query(const QString& str);

private:
    QSqlError initTables();
    QSqlError initRecords();
    QSqlDatabase db;
    QString connName;

};
