#include "SproutManager.h"
#include <QtCore>
#include <QtSql>

SproutManager::SproutManager(const QString& filePath, QObject* parent) :
        QObject(parent),
        filePath(filePath) {
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        throw std::runtime_error("Unable to load database. Needs the SQLITE driver");
    }
}

SproutManager::~SproutManager() {
    closeDb();
    qDebug() << "Destroy Sprout Manager" << filePath;
}

void SproutManager::create() {
    qDebug() << "Create Sprout Manager" << filePath;
    openDb();
    initTables();
}

void SproutManager::open() {
    qDebug() << "Open Sprout Mananger" << filePath;
    openDb();
}

void SproutManager::openDb() {
    connection = "sproute:" + filePath;
    db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName(filePath);
    if (!db.open()) {
        throw std::runtime_error(db.lastError().text().toStdString());
    }
}

void SproutManager::closeDb() {
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connection);
}

void SproutManager::initTables() {
    QSqlQuery q(db);
    q.exec("CREATE TABLE Defs("
               "name,"
               "value"
               ")");
    if (q.lastError().type() != QSqlError::NoError) {
        throw std::runtime_error(q.lastError().text().toStdString());
    }
}
