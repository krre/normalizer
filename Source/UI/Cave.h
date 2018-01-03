#pragma once
#include <QWidget>
#include <QString>
#include <QProcess>
#include <QTime>

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

signals:
    void outputMessage(const QString& message);

private slots:
    void onReadyRead();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    void timedOutputMessage(const QString& message);

    QString m_filePath;
    DatabaseManager* databaseManager;
    QProcess* process;
    QTime measureTime;
};
