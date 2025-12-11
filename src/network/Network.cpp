#include "api/Network.h"

namespace Api {

Network::Network(WebSocketClient* webSocketClient, QObject* parent) : QObject(parent), m_webSocketClient(webSocketClient) {

}

}
