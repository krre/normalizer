#include "Server.h"

namespace Api {

Server::Server(Network* network) : Controller(network) {

}

Controller::Name Server::name() const {
    return Name::Server;
}

Async::Task<Server::Attributes> Server::handshake() {
    auto response = co_await send(static_cast<MethodCode>(Method::Handshake));
    Attributes attributes;

    if (response.has_value()) {
        QDataStream stream(response.value());
        stream.setByteOrder(QDataStream::BigEndian);

        quint32 numVersion;
        stream >> numVersion;

        int major = numVersion / 1'000'000;
        int minor = (numVersion / 1'000) % 1'000;
        int patch = numVersion % 1'000;

        attributes.version = QVersionNumber(major, minor, patch);
    }

    co_return attributes;
}

}
