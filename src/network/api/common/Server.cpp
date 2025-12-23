#include "Server.h"
#include <QDebug>

namespace Api {

Server::Server(Network* network) : Controller(network) {

}

Controller::Name Server::name() const {
    return Name::Server;
}

Async::Task<Server::Attributes> Server::handshake() {
    QByteArray response = co_await send(static_cast<uint8_t>(Method::Handshake));
    qDebug() << response;

    Attributes state;
    co_return state;
}

}
