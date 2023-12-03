#pragma once
#include "network/controller/NetworkController.h"
#include "network/controller/Action.h"

namespace Controller {

class AbstractUser : public NetworkController {
public:
    AbstractUser(NetworkManager* networkManager);

    QString name() const override { return "user"; };
};

}
