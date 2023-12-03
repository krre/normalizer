#pragma once
#include "network/controller/AbstractController.h"

namespace Controller {

class AbstractAccount : public AbstractController {
public:
    AbstractAccount(NetworkManager* networkManager);
    QString name() const override { return "account"; };
};

}
