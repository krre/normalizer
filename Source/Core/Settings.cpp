#include "Settings.h"
#include <QtCore>

Settings::Settings(const QString& fileName, Format format) : QSettings(fileName, format) {

}

Settings::~Settings() {

}
