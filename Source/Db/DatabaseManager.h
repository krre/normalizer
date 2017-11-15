#pragma once
#include <QObject>

class DatabaseManager : public QObject {
    Q_OBJECT

public:
    DatabaseManager(QObject* parent = nullptr);
    ~DatabaseManager();
};
