#pragma once
#include "controller/NetworkController.h"

namespace Controller {

class AbstractAccount : public NetworkController {
public:
    AbstractAccount(NetworkManager* networkManager);
    QString name() const override { return "account"; };
};

}
