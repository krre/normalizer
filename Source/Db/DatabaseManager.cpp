#include "DatabaseManager.h"
#include <QtCore>
#include <QtSql>

DatabaseManager::DatabaseManager(const QString& filePath, QObject* parent) :
        QObject(parent) {
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        throw std::runtime_error("Unable to load database. Needs the SQLITE driver");
    }

    QFileInfo fi(filePath);
    bool dbExists = fi.exists();

    _connection = "irbis:" + filePath;
    _db = QSqlDatabase::addDatabase("QSQLITE", _connection);
    _db.setDatabaseName(filePath);
    if (!_db.open()) {
        throw std::runtime_error(_db.lastError().text().toStdString());
    }

    if (!dbExists) {
        initTables();
        initRecords();
    }
}

DatabaseManager::~DatabaseManager() {
    _db.close();
    _db = QSqlDatabase();
    QSqlDatabase::removeDatabase(_connection);
}

void DatabaseManager::initTables() {
    QSqlQuery q(_db);
    q.exec("CREATE TABLE Defs(name, value)");
    if (q.lastError().type() != QSqlError::NoError) {
        throw std::runtime_error(q.lastError().text().toStdString());
    }
}

void DatabaseManager::initRecords() {
    QSqlQuery q(_db);
    q.prepare("INSERT INTO Defs (name, value) "
                  "VALUES (:name, :value)");
    q.bindValue(":name", "IrbisCaveVersion");
    q.bindValue(":value", QCoreApplication::applicationVersion());
    q.exec();

    if (q.lastError().type() != QSqlError::NoError) {
        throw std::runtime_error(q.lastError().text().toStdString());
    }
}
