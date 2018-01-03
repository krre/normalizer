#pragma once
#include <Irbis/Core/Singleton.h>
#include <QSettings>

namespace IrbisUnitBuilder {

class Settings : public QSettings, public IrbisLib::Singleton<Settings> {

public:
    Settings(const QString& fileName, Format format);
    ~Settings();
};

} // IrbisUnitBuilder
