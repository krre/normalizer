#include <QtCore>
#include <QtSql>
#include "SproutDb.h"

QString SproutDb::create(const QString& path) {
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        return tr("Unable to load database. Needs the SQLITE driver");
    }
    connName = "sproute:" + path;
    db = QSqlDatabase::addDatabase("QSQLITE", connName);
    db.setDatabaseName(path);
    if (db.open()) {
        QSqlError err = initTables();
        if (err.type() != QSqlError::NoError) {
            return err.text();
        }
        err = initRecords();
        if (err.type() != QSqlError::NoError) {
            return err.text();
        }
    } else {
        return db.lastError().text();
    }
    return "";
}

QString SproutDb::open(const QString& path) {
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        return tr("Unable to load database. Needs the SQLITE driver");
    }
    connName = "sproute:" + path;
    db = QSqlDatabase::addDatabase("QSQLITE", connName);
    db.setDatabaseName(path);
    if (db.open()) {
        return "";
    } else {
        return db.lastError().text();
    }
}

void SproutDb::close() {
    db.close();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connName);
}

QVariantList SproutDb::query(const QString& str) {
    QSqlQuery q(db);
    q.exec(str);
    if (q.lastError().type() != QSqlError::NoError) {
        qDebug() << q.lastError().text();
    }

    QVariantList list;
    while (q.next()) {
        QVariantMap map;
        QSqlRecord rec = q.record();
        for (int i = 0; i < rec.count(); i++) {
            map[rec.fieldName(i)] = rec.value(i);
        }
        list.append(map);
    }

    return list;
}

QSqlError SproutDb::initTables() {
    QSqlQuery q(db);
    q.exec("CREATE TABLE Defs("
               "name,"
               "value"
               ")");
    q.exec("CREATE TABLE Modules("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name"
               ")");
    q.exec("CREATE TABLE Functions("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "moduleId INTEGER,"
               "name"
               ")");
    q.exec("CREATE TABLE Expressions("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "functionId INTEGER,"
               "name"
               ")");
    q.exec("CREATE TABLE Arguments("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "expressionId,"
               "arg"
               ")");
    q.exec("CREATE TABLE Comments("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "comment"
               ")");

    return q.lastError();
}

QSqlError SproutDb::initRecords() {
    QSqlQuery q(db);
    q.prepare("INSERT INTO Defs (name, value) "
                  "VALUES (:name, :value)");
    q.bindValue(":name", "SproutEVersion");
    q.bindValue(":value", QCoreApplication::applicationVersion());
    q.exec();

    return q.lastError();
}
