#include "Server.h"

namespace Api {

Server::Server(Network* network) : Controller(network) {

}

Controller::Name Server::name() const {
    return Name::Server;
}

Server::State Server::handshake() {
    send(static_cast<uint8_t>(Method::Handshake));

    State state;
    return state;
}

}
