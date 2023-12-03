#pragma once
#include "network/controller/AbstractController.h"
#include "network/controller/Action.h"

namespace Controller {

class AbstractUser : public AbstractController {
public:
    AbstractUser(NetworkManager* networkManager);

    QString name() const override { return "user"; };
};

}
