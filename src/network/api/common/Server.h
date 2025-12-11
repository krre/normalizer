#pragma once
#include "network/api/Controller.h"
#include <QVersionNumber>

namespace Api {

class Server : public Controller {
public:
    Server(Network* network);

    QVersionNumber version() const;
};

}
