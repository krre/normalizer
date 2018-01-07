#pragma once
#include <QObject>
#include <QSqlDatabase>

namespace IrbisUnitBuilder {

class DatabaseManager : public QObject {
    Q_OBJECT

public:
    DatabaseManager(const QString& filePath, QObject* parent = nullptr);
    ~DatabaseManager();
    void addUnit(const QString& name = QString());

private:
    int getNextId(const QString& table);
    QString createNumeredName(const QString& table, const QString& name);

    QSqlDatabase db;
    QString connection;
};

} // IrbisUnitBuilder
