#pragma once
#include "AbstractSettingsManager.h"

class SettingsManager : public AbstractSettingsManager {
public:
    void setServerAddress(const ServerAddress& serverAddress) override;
    ServerAddress serverAddress() const override;

    void setAccount(const Account& account) override;
    Account account() const override;
};
