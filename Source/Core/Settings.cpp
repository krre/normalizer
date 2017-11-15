#include "Settings.h"
#include "Defines.h"
#include <QtCore>

Settings::Settings(const QString& fileName, Format format) : QSettings(fileName, format) {

}

Settings::~Settings() {

}

QString Settings::readWorkspace() {
    return value("Path/workspace", QDir::homePath() + "/" + WORKSPACE_DIRECTORY).toString();
}

bool Settings::readRestoreSession() {
    return value("MainWindow/restoreSession", true).toBool();
}
