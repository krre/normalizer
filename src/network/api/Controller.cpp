#include "Controller.h"
#include "network/Network.h"

namespace Api {

Controller::Controller(Network* network) : m_network(network) {

}

Network* Controller::network() const {
    return m_network;
}

Async::Task<QByteArray> Controller::send(MethodCode method, const QByteArray& params) {
    QByteArray message;
    message += static_cast<ControllerCode>(name());
    message += method;
    message += static_cast<uint16_t>(params.size());
    message += params;

    co_return co_await m_network->sendMessage(message);
}

}
