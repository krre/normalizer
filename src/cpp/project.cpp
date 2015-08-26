#include "project.h"

Project::Project()
{

}

bool Project::create(const QString &path, const QString &name)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", path);
    db.setDatabaseName(path);
    if (!db.open()) {
         qDebug("Error occurred opening the database");
         qDebug("%s", qPrintable(db.lastError().text()));
         return -1;
    }
    initDb(db);
    return true;
}

void Project::initDb(const QSqlDatabase &db)
{
    QSqlQuery query(db);
    query.exec("CREATE TABLE Defs(version)");
    query.exec("CREATE TABLE Modules(id, name)");
    query.exec("CREATE TABLE Functions(id, name, command, argument)");
    query.exec("CREATE TABLE Comments(id, comment)");
}

