#pragma once
#include <QtCore>
#include <QtSql>

class Project : public QObject
{
    Q_OBJECT
public:
    Project();
    Q_INVOKABLE bool create(const QString& path, const QString& projectName);

private:
    void initTables(const QSqlDatabase& db);
    void initRecords(const QSqlDatabase& db, const QString& projectName);
};
