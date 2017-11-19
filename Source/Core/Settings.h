#pragma once
#include <Irbis/Core/Singleton.h>
#include <QSettings>

class Settings : public QSettings, public Singleton<Settings> {

public:
    Settings(const QString& fileName, Format format);
    ~Settings();

    QString readWorkspace();
    bool readRestoreSession();
};
