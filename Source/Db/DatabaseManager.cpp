#include "DatabaseManager.h"
#include <QtCore>
#include <QtSql>

namespace IrbisCave {

DatabaseManager::DatabaseManager(const QString& filePath, QObject* parent) :
        QObject(parent) {
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        throw std::runtime_error("Unable to load database. Needs the SQLITE driver");
    }

    QFileInfo fi(filePath);
    bool dbExists = fi.exists();

    connection = "irbis:" + filePath;
    db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName(filePath);
    if (!db.open()) {
        throw std::runtime_error(db.lastError().text().toStdString());
    }

    if (!dbExists) {
        initTables();
        initRecords();
    }
}

DatabaseManager::~DatabaseManager() {
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connection);
}

void DatabaseManager::initTables() {
    QSqlQuery q(db);
    q.exec("CREATE TABLE IF NOT EXISTS Defs(name, value)");

    q.exec("CREATE TABLE IF NOT EXISTS Modules("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "name)");

    q.exec("CREATE TABLE IF NOT EXISTS Functions("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "name,"
           "module_id)");

    q.exec("CREATE TABLE IF NOT EXISTS Expressions("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "name,"
           "function_id)");

    if (q.lastError().type() != QSqlError::NoError) {
        throw std::runtime_error(q.lastError().text().toStdString());
    }
}

void DatabaseManager::initRecords() {
    QSqlQuery q(db);
    q.prepare("INSERT INTO Defs (name, value) "
                  "VALUES (:name, :value)");
    q.bindValue(":name", "IrbisCaveVersion");
    q.bindValue(":value", QCoreApplication::applicationVersion());
    q.exec();

    if (q.lastError().type() != QSqlError::NoError) {
        throw std::runtime_error(q.lastError().text().toStdString());
    }
}

} // IrbisCave
