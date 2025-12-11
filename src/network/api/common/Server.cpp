#include "Server.h"

namespace Api {

Server::Server(Network* network) : Controller(network) {

}

QVersionNumber Server::version() const {
    return QVersionNumber();
}

}
