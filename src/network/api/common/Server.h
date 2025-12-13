#pragma once
#include "network/api/Controller.h"
#include <QVersionNumber>

namespace Api {

class Server : public Controller {
public:
    enum class Method : uint8_t {
        Handshake = 0x00
    };

    struct State {
        QVersionNumber version;
    };

    Server(Network* network);

    Name name() const;

    State handshake();
};

}
