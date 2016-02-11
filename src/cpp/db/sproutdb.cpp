#include "sproutdb.h"

SproutDb::SproutDb()
{

}

QString SproutDb::create(const QString& path)
{
    if (!QSqlDatabase::drivers().contains("QSQLITE")) {
        return tr("Unable to load database. Needs the SQLITE driver");
    }
    db = QSqlDatabase::addDatabase("QSQLITE", "usilage:" + path);
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

QSqlError SproutDb::initTables()
{
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

QSqlError SproutDb::initRecords()
{
    QSqlQuery q(db);
    q.prepare("INSERT INTO Defs (name, value) "
                  "VALUES (:name, :value)");
    q.bindValue(":name", "UsilageVersion");
    q.bindValue(":value", QCoreApplication::applicationVersion());
    q.exec();

    return q.lastError();
}
