#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include <QtCore>

class Interpretator: public QProcess
{
    Q_OBJECT
public:
    Interpretator();
    Q_INVOKABLE void run(const QString &sproutPath, const QString &sourcePath);

signals:
    void consoleMessage(const QString &message);

private slots:
    void onStarted();
    void onFinished(int exitCode);
    void onReadyRead();
    void onError(QProcess::ProcessError error);
};

#endif // INTERPRETATOR_H
