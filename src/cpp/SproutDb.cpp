#include "SproutDb.h"

SproutDb::SproutDb()
{

}

SproutDb::~SproutDb()
{
    db.close();
//    qDebug() << "CLOSE";
}

bool SproutDb::create(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE", path);
    db.setDatabaseName(path);
    db.open();
    initDb();
    return true;
}

void SproutDb::open(const QString &path)
{
    db = QSqlDatabase::database(path);
    //    qDebug() << "OPEN";
}

void SproutDb::initDb()
{
    QSqlQuery query(db);
    query.exec("CREATE TABLE Defs(version)");
    bool result = query.exec("INSERT INTO Defs (version) VALUES ('0.1.0')");
    if (!result) {

    }
    qDebug() << "insert" << result;
}


