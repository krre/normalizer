#include "Controller.h"
#include "network/Network.h"

namespace Api {

Controller::Controller(Network* network) : m_network(network) {

}

Network* Controller::network() const {
    return m_network;
}

void Controller::send(uint8_t method, const QByteArray& params) {
    QByteArray message;
    message += static_cast<uint8_t>(name());
    message += method;
    message += static_cast<uint16_t>(params.size());
    message += params;

    m_network->sendMessage(message);
}

}
