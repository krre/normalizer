#include "Network.h"
#include "WebSocketClient.h"
#include "core/async/Awaiter.h"

NetworkWaker::NetworkWaker(WebSocketClient* webSocketClient) {
    QObject::connect(webSocketClient, &WebSocketClient::messageReceived, [this] (const QByteArray& message) {
        awaiter()->resume(message);
    });
}

Network::Network(WebSocketClient* webSocketClient, QObject* parent) : QObject(parent), m_webSocketClient(webSocketClient) {

}

Async::Awaiter<QByteArray> Network::sendMessage(const QByteArray& message) {
    m_webSocketClient->sendMessage(message);
    return Async::Awaiter<QByteArray>(std::make_unique<NetworkWaker>(m_webSocketClient));
}
