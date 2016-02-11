#include "sproutdb.h"

SproutDb::SproutDb()
{

}

bool SproutDb::create(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE", "usilage:" + path);
    db.setDatabaseName(path);
    return db.open();
}
