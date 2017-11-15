#pragma once
#include <QWidget>
#include <QString>

class DatabaseManager;

class Cave : public QWidget {
    Q_OBJECT

public:
    Cave(const QString& filePath);
    ~Cave();

    QString filePath() const;

private:
    QString _filePath;
    DatabaseManager* _databaseManager;
};
