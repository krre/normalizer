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
//    qDebug() << "NEW";
    return true;
}

void SproutDb::open(const QString &path)
{
    db = QSqlDatabase::database(path);
//    qDebug() << "OPEN";
}


