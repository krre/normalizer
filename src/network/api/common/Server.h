#pragma once
#include "network/api/Controller.h"
#include <QVersionNumber>

namespace Api {

class Server : public Controller {
public:
    struct State {
        QVersionNumber version;
    };

    Server(Network* network);

    State handshake() const;
};

}
