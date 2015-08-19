#pragma once
#include <QtCore>

class Interpreter: public QProcess
{
    Q_OBJECT
public:
    Interpreter();
    Q_INVOKABLE void run(const QString &sproutPath, const QString &sourcePath);

signals:
    void consoleMessage(const QString &message);

private slots:
    void onStarted();
    void onFinished(int exitCode);
    void onReadyRead();
    void onError(QProcess::ProcessError error);
};
