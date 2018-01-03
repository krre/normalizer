#pragma once
#include <QObject>
#include <QSqlDatabase>

namespace IrbisCave {

class DatabaseManager : public QObject {
    Q_OBJECT

public:
    DatabaseManager(const QString& filePath, QObject* parent = nullptr);
    ~DatabaseManager();

private:
    void initTables();
    void initRecords();

    QSqlDatabase db;
    QString connection;
};

} // IrbisCave
