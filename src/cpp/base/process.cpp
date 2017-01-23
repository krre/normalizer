#include "process.h"
#include <QtCore>

Process::Process() {
    setProcessChannelMode(QProcess::MergedChannels);

    connect(this, SIGNAL(started()), this, SLOT(onStarted()));
    connect(this, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
    connect(this, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onError(QProcess::ProcessError)));
    connect(this, SIGNAL(finished(int)), this, SLOT(onFinished(int)));
}

void Process::run(const QString& sproutPath, const QString& sourcePath) {
    start(sproutPath + " " + sourcePath);
}

void Process::onStarted() {
    emit message("Starting run " + arguments().at(0) + "...");
}

void Process::onFinished(int exitCode) {
    emit message(arguments().at(0) + " exited with code " + QString::number(exitCode));
    emit message("");
}

void Process::onReadyRead() {
    emit message(readAllStandardOutput());
}

void Process::onError(ProcessError error) {
    emit message("Error: " + QString::number(error));
}
