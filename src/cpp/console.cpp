#include "console.h"
#include "settings.h"

Console::Console()
{
    setProcessChannelMode(QProcess::MergedChannels);

    connect(this, SIGNAL(started()), this, SLOT(onStarted()));
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onError(QProcess::ProcessError)));
    connect(this, SIGNAL(finished(int)), this, SLOT(onFinished(int)));
}

void Console::run(const QString& binPath)
{
    qDebug() << "run: " << binPath;
}

void Console::build(const QString &sproutPath, const QString &sourcePath)
{
    start(sproutPath + " " + sourcePath);
}

void Console::onStarted()
{
    emit message("Starting " + arguments().at(0) + "...");
}

void Console::onFinished(int exitCode)
{
    emit message(arguments().at(0) + " exited with code " + QString::number(exitCode));
    emit message("");
}

void Console::onReadyRead()
{
    emit message(readAllStandardOutput());
}

void Console::onError(ProcessError error)
{
    emit message("Error: " + QString::number(error));
}
