#include "interpreter.h"
#include "settings.h"

Interpreter::Interpreter()
{
    connect(this, SIGNAL(started()), this, SLOT(onStarted()));
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onError(QProcess::ProcessError)));
    connect(this, SIGNAL(finished(int)), this, SLOT(onFinished(int)));
}

void Interpreter::run(const QString &sproutPath, const QString &sourcePath)
{
    setProcessChannelMode(QProcess::MergedChannels);
    start(sproutPath + " " + sourcePath);
}

void Interpreter::onStarted()
{
    emit consoleMessage("Starting " + arguments().at(0) + "...");
}

void Interpreter::onFinished(int exitCode)
{
    emit consoleMessage(arguments().at(0) + " exited with code " + QString::number(exitCode));
    emit consoleMessage("");
}

void Interpreter::onReadyRead()
{
    emit consoleMessage(readAllStandardOutput());
}

void Interpreter::onError(ProcessError error)
{
    emit consoleMessage("Error: " + QString::number(error));
}
