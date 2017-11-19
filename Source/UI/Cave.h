#pragma once
#include <QWidget>
#include <QString>

class DatabaseManager;
class QProcess;

class Cave : public QWidget {
    Q_OBJECT

public:
    Cave(const QString& filePath);
    ~Cave();

    void build();
    void stop();

    QString filePath() const;

private:
    QString _filePath;
    DatabaseManager* _databaseManager;
    QProcess* _process;
};
