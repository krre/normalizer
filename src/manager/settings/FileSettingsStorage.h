#pragma once
#include "SettingsStorage.h"

class FileSettingsStorage : public SettingsStorage {
public:
    FileSettingsStorage();

    void setMainWindow(const MainWindow& mainWindow) override;
    MainWindow mainWindow() const override;
    bool containsGeometry() const override;

    void setServerAddress(const ServerAddress& serverAddress) override;
    ServerAddress serverAddress() const override;

    void setAccount(const Account& account) override;
    Account account() const override;
};
