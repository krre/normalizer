#include "Controller.h"
#include "network/Network.h"

namespace Api {

Controller::Controller(Network* network) : m_network(network) {

}

Network* Controller::network() const {
    return m_network;
}

Async::Task<std::expected<QByteArray, ErrorCode>> Controller::send(MethodCode method, const QByteArray& params) {
    QByteArray message;
    message += static_cast<ControllerCode>(name());
    message += method;
    message += static_cast<uint16_t>(params.size());
    message += params;

    QByteArray response = co_await *m_network->sendMessage(message).data();

    if (static_cast<ResponseType>(response.at(0)) == ResponseType::Success) {
        uint8_t size = response.at(1);
        co_return response.right(size);
    } else {
        co_return std::unexpected(response.at(1));
    }
}

}
