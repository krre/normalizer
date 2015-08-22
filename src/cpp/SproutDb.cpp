#include "SproutDb.h"

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
         qDebug("Error occurred opening the database.");
         qDebug("%s.", qPrintable(db.lastError().text()));
         return -1;
    }
    initDb();
    return true;
}

void SproutDb::open(const QString &path)
{
    db = QSqlDatabase::database(path);
}

void SproutDb::initDb()
{
    QSqlQuery query(db);
    query.exec("CREATE TABLE Defs(version)");
    query.exec("CREATE TABLE Functions(name, command, argument)");
    bool result = query.exec("INSERT INTO Defs (version) VALUES ('0.1.0')");
    if (!result) {

    }
    qDebug() << "insert" << result;
}


