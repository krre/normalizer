#pragma once
#include <QObject>
#include <QSqlDatabase>

class SproutManager : public QObject {
    Q_OBJECT
public:
    explicit SproutManager(const QString& filePath, QObject* parent = nullptr);
    ~SproutManager();
    void create();
    void open();

private:
    QString filePath;
    QSqlDatabase db;
    QString connection;

    void openDb();
    void closeDb();
    void initTables();
};
