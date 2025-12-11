#include "ApiNetwork.h"

ApiNetwork::ApiNetwork(WebSocketClient* webSocketClient, QObject* parent) : QObject(parent), m_webSocketClient(webSocketClient) {

}
