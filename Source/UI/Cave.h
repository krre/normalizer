#pragma once
#include <QWidget>
#include <QString>
#include <QProcess>
#include <QTime>

namespace IrbisCave {

class DatabaseManager;

class Cave : public QWidget {
    Q_OBJECT

public:
    Cave(const QString& filePath);
    ~Cave();

    void build();
    void stop();

    QString getFilePath() const;

signals:
    void outputMessage(const QString& message);

private slots:
    void onReadyRead();
    void onFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    void timedOutputMessage(const QString& message);

    QString filePath;
    DatabaseManager* databaseManager;
    QProcess* process;
    QTime measureTime;
};

} // IrbisCave
