#pragma once
#include "controller/NetworkController.h"
#include "controller/Action.h"

namespace Controller {

class AbstractUser : public NetworkController {
public:
    AbstractUser(NetworkManager* networkManager);

    QString name() const override { return "user"; };
};

}
