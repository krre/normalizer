#pragma once
#include "AbstractAccount.h"

namespace Controller {

class Account : public AbstractAccount {
public:
    Account(NetworkManager* networkManager);
};

}
