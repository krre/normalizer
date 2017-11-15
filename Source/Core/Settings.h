#pragma once
#include "Singleton.h"
#include <QSettings>

class Settings : public QSettings, public Singleton<Settings> {

public:
    Settings();
    ~Settings();
};
