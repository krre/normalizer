#include "NetworkApi.h"

NetworkApi::NetworkApi(WebSocketClient* webSocketClient, QObject* parent) : QObject(parent), m_webSocketClient(webSocketClient) {

}
