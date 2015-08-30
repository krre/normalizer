#include "project.h"

Project::Project()
{

}

bool Project::create(const QString& path, const QString& projectName)
{
    {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", path);
        db.setDatabaseName(path);
        if (!db.open()) {
             qDebug("Error occurred opening the database");
             qDebug("%s", qPrintable(db.lastError().text()));
             return false;
        }
        initTables(db);
        initRecords(db, projectName);
    }
    QSqlDatabase::removeDatabase(path);
    return true;
}

void Project::initTables(const QSqlDatabase& db)
{
    QSqlQuery query(db);
    query.exec("CREATE TABLE Defs("
               "name,"
               "value"
               ")");
    query.exec("CREATE TABLE Modules("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "name"
               ")");
    query.exec("CREATE TABLE Functions("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "module INTEGER,"
               "name,"
               "command,"
               "argument"
               ")");
    query.exec("CREATE TABLE Commands("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "function INTEGER,"
               "name,"
               "args"
               ")");
    query.exec("CREATE TABLE Comments("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "comment"
               ")");

}

void Project::initRecords(const QSqlDatabase& db, const QString& projectName)
{
    QSqlQuery query(db);
    query.prepare("INSERT INTO Defs (name, value) "
                  "VALUES (:name, :value)");
    query.bindValue(":name", "version");
    query.bindValue(":value", "0.1.0");
    bool result = query.exec();
    if (!result) {
        qDebug("Error occurred insert record");
        qDebug("%s", qPrintable(query.lastError().text()));
    }

    query.bindValue(":name", "project");
    query.bindValue(":value", projectName);
    result = query.exec();
    if (!result) {
        qDebug("Error occurred insert record");
        qDebug("%s", qPrintable(query.lastError().text()));
    }
}

