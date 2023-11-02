#pragma once
#include "AbstractNetworkManager.h"

class NetworkManager : public AbstractNetworkManager {
public:
    NetworkManager();

    Async::Task<QString> registerUser(const QString& url, const User& user) override;
};
