#include "Server.h"

namespace Api {

Server::Server(Network* network) : Controller(network) {

}

Controller::Name Server::name() const {
    return Name::Server;
}

Server::State Server::handshake() const {
    State state;
    return state;
}

}
