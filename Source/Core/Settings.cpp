#include "Settings.h"
#include <QtCore>

namespace IrbisUnitBuilder {

Settings::Settings(const QString& fileName, Format format) : QSettings(fileName, format) {

}

Settings::~Settings() {

}

} // IrbisUnitBuilder
