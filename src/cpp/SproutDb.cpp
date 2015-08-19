#include "SproutDb.h"

SproutDb::SproutDb()
{

}

SproutDb::~SproutDb()
{
    db.close();
}

void SproutDb::create(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);
    db.open();
}


