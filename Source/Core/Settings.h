#pragma once
#include <Irbis/Core/Singleton.h>
#include <QSettings>

namespace IrbisCave {

class Settings : public QSettings, public IrbisLib::Singleton<Settings> {

public:
    Settings(const QString& fileName, Format format);
    ~Settings();

    QString readWorkspace();
    bool readRestoreSession();
};

} // IrbisCave
