#pragma once
#include "SettingsStorage.h"

class FileSettingsStorage : public SettingsStorage {
public:
    void setServerAddress(const ServerAddress& serverAddress) override;
    ServerAddress serverAddress() const override;

    void setAccount(const Account& account) override;
    Account account() const override;
};
