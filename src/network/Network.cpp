#include "Network.h"
#include "WebSocketClient.h"

namespace Api {

Network::Network(WebSocketClient* webSocketClient, QObject* parent) : QObject(parent), m_webSocketClient(webSocketClient) {

}

void Network::sendMessage(const QByteArray& message) {
    m_webSocketClient->sendMessage(message);
}

}
