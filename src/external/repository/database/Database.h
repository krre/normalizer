#pragma once
#include <QSqlDatabase>

class Database {
public:
    Database();

private:
    QSqlDatabase m_db;
};
