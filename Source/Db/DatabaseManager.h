#pragma once
#include <QObject>
#include <QSqlDatabase>

namespace IrbisCave {

class DatabaseManager : public QObject {
    Q_OBJECT

public:
    DatabaseManager(const QString& filePath, QObject* parent = nullptr);
    ~DatabaseManager();
    void addModule(const QString& name = QString());

private:
    void initTables();
    void initRecords();
    int getNextId(const QString& table);
    QString createNumeredName(const QString& table, const QString& name);

    QSqlDatabase db;
    QString connection;
};

} // IrbisCave
