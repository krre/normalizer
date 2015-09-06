#include "sproutdb.h"

SproutDb::SproutDb()
{

}

SproutDb::~SproutDb()
{
    db.close();
}

void SproutDb::open(const QString& path)
{
    db = QSqlDatabase::addDatabase("QSQLITE", path);
    db.setDatabaseName(path);
    if (!db.open()) {
         qDebug("Error occurred opening the database");
         qDebug("%s", qPrintable(db.lastError().text()));
    }
}

void SproutDb::close()
{
    db.close();
    QString connection = db.connectionName();
    db = QSqlDatabase();
    QSqlDatabase::removeDatabase(connection);
}

QVariantList SproutDb::readRecords(const QString& sql)
{
    QSqlQuery query(db);
    bool result = query.exec(sql);
    if (!result) {
        qDebug("Error occurred insert record");
        qDebug("%s", qPrintable(query.lastError().text()));
        return QVariantList();
    }

    QVariantList list;
    QVariantMap map;
    QSqlRecord record = query.record();
    int columnCount = record.count();
    while (query.next()) {
        map.clear();
        for (int i = 0; i < columnCount; i++) {
            map[record.fieldName(i)] = query.value(i).toString();
        }
        list << map;
    }
    return list;
}

void SproutDb::insertRecord(const QString& sql)
{
    QSqlQuery query(db);
    bool result = query.exec(sql);
    if (!result) {
        qDebug("Error occurred insert record");
        qDebug("%s", qPrintable(query.lastError().text()));
    }
}

void SproutDb::updateRecord(const QString& sql)
{
    QSqlQuery query(db);
    bool result = query.exec(sql);
    if (!result) {
        qDebug("Error occurred update record");
        qDebug("%s", qPrintable(query.lastError().text()));
    }
}

void SproutDb::deleteRecord(const QString& sql)
{
    QSqlQuery query(db);
    bool result = query.exec(sql);
    if (!result) {
        qDebug("Error occurred update record");
        qDebug("%s", qPrintable(query.lastError().text()));
    }
}


