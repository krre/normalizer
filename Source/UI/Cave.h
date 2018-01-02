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

private slots:
    void onReadyRead();

private:
    QString m_filePath;
    DatabaseManager* databaseManager;
    QProcess* process;
};
