#pragma once
#include <QString>

class NetworkManager;

namespace Controller {

class AbstractController {
public:
    AbstractController(NetworkManager* networkManager);

    virtual QString name() const = 0;
    NetworkManager* networkManager() const;

private:
    NetworkManager* m_networkManager = nullptr;
};

}
