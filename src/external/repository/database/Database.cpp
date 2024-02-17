#include "Database.h"
#include <QtSql>

Database::Database() {
    m_db = QSqlDatabase::addDatabase("QSQLITE");
}
