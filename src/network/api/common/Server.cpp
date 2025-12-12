#include "Server.h"

namespace Api {

Server::Server(Network* network) : Controller(network) {

}

Server::State Server::handshake() const {
    State state;
    return state;
}

}
