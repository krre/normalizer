#pragma once
#include "AbstractUser.h"

namespace Controller {

class User : public AbstractUser {
public:
    User(NetworkManager* networkManager);
};

}
