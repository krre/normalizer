#include "sproutdb.h"

SproutDb::SproutDb()
{

}

SproutDb::~SproutDb()
{
    db.close();
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


