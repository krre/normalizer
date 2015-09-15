#pragma once
#include <QtCore>

class Console: public QProcess
{
    Q_OBJECT
public:
    Console();
    Q_INVOKABLE void run(const QString& binPath);
    Q_INVOKABLE void build(const QString& sproutPath, const QString& sourcePath);

signals:
    void message(const QString& message);

private slots:
    void onStarted();
    void onFinished(int exitCode);
    void onReadyRead();
    void onError(QProcess::ProcessError error);
};
