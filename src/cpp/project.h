#pragma once
#include <QtCore>
#include <QtSql>

class Project : public QObject
{
    Q_OBJECT
public:
    Project();
    Q_INVOKABLE bool create(const QString &path);

private:
    void initDb(const QSqlDatabase &db);
};
