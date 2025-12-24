#include "Server.h"
#include <QDebug>

namespace Api {

Server::Server(Network* network) : Controller(network) {

}

Controller::Name Server::name() const {
    return Name::Server;
}

Async::Task<Server::Attributes> Server::handshake() {
    auto response = co_await send(static_cast<MethodCode>(Method::Handshake));

    if (response.has_value()) {
        qDebug() << response.value();
    }

    Attributes state;
    co_return state;
}

}
