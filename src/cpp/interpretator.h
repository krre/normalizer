#ifndef INTERPRETATOR_H
#define INTERPRETATOR_H

#include <QtCore>

class Interpretator: public QProcess
{
    Q_OBJECT
public:
    Interpretator();
    Q_INVOKABLE void run(const QString filePath);

signals:
    void consoleMessage(const QString &message);

};

#endif // INTERPRETATOR_H
