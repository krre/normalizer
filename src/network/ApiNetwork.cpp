#include "api/ApiNetwork.h"

namespace Api {

ApiNetwork::ApiNetwork(WebSocketClient* webSocketClient, QObject* parent) : QObject(parent), m_webSocketClient(webSocketClient) {

}

}
