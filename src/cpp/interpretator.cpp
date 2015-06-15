#include "interpretator.h"
#include "settings.h"

Interpretator::Interpretator()
{
    connect(this, SIGNAL(started()), this, SLOT(onStarted()));
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onError(QProcess::ProcessError)));
    connect(this, SIGNAL(finished(int)), this, SLOT(onFinished(int)));
}

void Interpretator::run(const QString &sproutPath, const QString &sourcePath)
{
    setProcessChannelMode(QProcess::MergedChannels);
    start(sproutPath + " " + sourcePath);
}

void Interpretator::onStarted()
{
    emit consoleMessage("Starting " + arguments().at(0) + "...");
}

void Interpretator::onFinished(int exitCode)
{
    emit consoleMessage(arguments().at(0) + " exited with code " + QString::number(exitCode));
}

void Interpretator::onReadyRead()
{
    emit consoleMessage(readAllStandardOutput());
}

void Interpretator::onError(ProcessError error)
{
    emit consoleMessage("Error: " + QString::number(error));
}
