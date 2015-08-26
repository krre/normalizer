#include "sproutdb.h"

SproutDb::SproutDb()
{

}

SproutDb::~SproutDb()
{
    db.close();
}

bool SproutDb::create(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE", path);
    db.setDatabaseName(path);
    if (!db.open()) {
         qDebug("Error occurred opening the database");
         qDebug("%s", qPrintable(db.lastError().text()));
         return -1;
    }
    initDb();
    return true;
}

void SproutDb::open(const QString &path)
{
    db = QSqlDatabase::database(path);
}

void SproutDb::readRecord()
{

}

void SproutDb::insertRecord()
{

}

void SproutDb::updateRecord()
{

}

void SproutDb::deleteRecord()
{

}

void SproutDb::initDb()
{
    QSqlQuery query(db);
    query.exec("CREATE TABLE Defs(version)");
    query.exec("CREATE TABLE Modules(id, name)");
    query.exec("CREATE TABLE Functions(id, name, command, argument)");
    query.exec("CREATE TABLE Comments(id, comment)");
}


