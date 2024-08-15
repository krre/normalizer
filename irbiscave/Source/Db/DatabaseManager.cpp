#include "DatabaseManager.h"
#include "Core/Defines.h"
#include <QtCore>
#include <QtSql>
#include <IrbisLib/Core/Utils.h>

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
        createPrimaryTables();
    }

    if (checkStorageOutOfDate()) {
        qDebug() << "Storage version out of date. Update tables";
        initTables();
        initRecords();
    }
}

DatabaseManager::~DatabaseManager() {
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connection);
}

void DatabaseManager::addModule(const QString& name) {
    QString value = name;
    if (value.isEmpty()) {
        value = createNumeredName("Modules", "Module");
    }
    QSqlQuery q(db);
    q.exec(QString("INSERT INTO Modules (name) VALUES ('%1')").arg(value));

    if (q.lastError().type() != QSqlError::NoError) {
        throw std::runtime_error(q.lastError().text().toStdString());
    }
}

void DatabaseManager::createPrimaryTables() {
    QSqlQuery q(db);

    q.exec("CREATE TABLE Versions("
           "name,"
           "version,"
           "api)");

    q.prepare("INSERT INTO Versions VALUES (:name, :version, :api)");
    q.bindValue(":name", "IrbisCave");
    q.bindValue(":version", IBRISCAVE_VERSION);
    q.bindValue(":api", IrbisLib::Utils::versionToApi(IBRISCAVE_VERSION));
    q.exec();

    q.bindValue(":name", "Irbis");
    q.bindValue(":version", IBRIS_VERSION);
    q.bindValue(":api", IrbisLib::Utils::versionToApi(IBRIS_VERSION));
    q.exec();

    q.bindValue(":name", "Storage");
    q.bindValue(":version", IBRIS_STORAGE_VERSION);
    q.bindValue(":api", IrbisLib::Utils::versionToApi(IBRIS_STORAGE_VERSION));
    q.exec();

    if (q.lastError().type() != QSqlError::NoError) {
        throw std::runtime_error(q.lastError().text().toStdString());
    }
}

bool DatabaseManager::checkStorageOutOfDate() {
    QSqlQuery q(db);
    q.exec("SELECT api FROM Versions WHERE name='Storage'");
    q.last();
    return IrbisLib::Utils::versionToApi(IBRIS_STORAGE_VERSION) > q.value("api").toInt();
}

void DatabaseManager::initTables() {
    QSqlQuery q(db);

    q.exec("CREATE TABLE IF NOT EXISTS Units("
           "id INTEGER PRIMARY KEY AUTOINCREMENT,"
           "name,"
           "model,"
           "description)");

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

    q.exec(QString("UPDATE Versions SET api='%1' WHERE name='Storage'").arg(IrbisLib::Utils::versionToApi(IBRIS_STORAGE_VERSION)));

    if (q.lastError().type() != QSqlError::NoError) {
        throw std::runtime_error(q.lastError().text().toStdString());
    }
}

void DatabaseManager::initRecords() {

}

int DatabaseManager::getNextId(const QString& table) {
    QSqlQuery q(db);
    q.exec(QString("SELECT * FROM SQLITE_SEQUENCE WHERE name='%1'").arg(table));
    q.last();
    return q.value(1).toInt() + 1; // get seq value and return next
}

// Create numered name from name and its record id
QString DatabaseManager::createNumeredName(const QString& table, const QString& name) {
    int dimension = 3; // eg Module.004
    QString zeroPaddingValue = QString("%1").arg(getNextId(table), dimension, 10, QChar('0'));
    return QString("%1.%2").arg(name).arg(zeroPaddingValue);
}

} // IrbisCave
