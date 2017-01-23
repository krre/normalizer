#pragma once
#include <QtCore>

class Process: public QProcess {
    Q_OBJECT
public:
    Process();
    Q_INVOKABLE void run(const QString& sproutPath, const QString& sourcePath);

signals:
    void message(const QString& message);

private slots:
    void onStarted();
    void onFinished(int exitCode);
    void onReadyRead();
    void onError(QProcess::ProcessError error);
};
