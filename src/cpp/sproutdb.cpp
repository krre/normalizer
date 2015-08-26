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
    db = QSqlDatabase::addDatabase("QSQLITE", path);
    db.setDatabaseName(path);
    if (!db.open()) {
         qDebug("Error occurred opening the database");
         qDebug("%s", qPrintable(db.lastError().text()));
    }
}

QVariantMap SproutDb::readRecord(const QString &table)
{
    QSqlQuery query(db);
    bool result = query.exec("SELECT * FROM " + table);
    if (!result) {
        qDebug("Error occurred insert record");
        qDebug("%s", qPrintable(query.lastError().text()));
        return QVariantMap();
    }

    QVariantMap map;
    while (query.next()) {
        map[query.value(0).toString()] = query.value(1).toString();
    }
    return map;
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


