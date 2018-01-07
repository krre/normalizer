#include "DatabaseManager.h"
#include <QtCore>
#include <QtSql>
#include <IrbisLib/Core/Utils.h>

namespace IrbisUnitBuilder {

DatabaseManager::DatabaseManager(const QString& filePath, QObject* parent) :
        QObject(parent) {
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        throw std::runtime_error("Unable to load database. Needs the SQLITE driver");
    }

    connection = "irbis:" + filePath;
    db = QSqlDatabase::addDatabase("QSQLITE", connection);
    db.setDatabaseName(filePath);
    if (!db.open()) {
        throw std::runtime_error(db.lastError().text().toStdString());
    }
}

DatabaseManager::~DatabaseManager() {
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connection);
}

QString DatabaseManager::addUnit() {
    QString name = createNumeredName("Units", "Unit");

    QSqlQuery q(db);
    q.exec(QString("INSERT INTO Units (name) VALUES ('%1')").arg(name));

    if (q.lastError().type() != QSqlError::NoError) {
        throw std::runtime_error(q.lastError().text().toStdString());
    }

    return name;
}

QSqlDatabase& DatabaseManager::getDb() {
    return db;
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

} // IrbisUnitBuilder
