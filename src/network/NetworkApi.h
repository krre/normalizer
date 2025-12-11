#pragma once
#include <QObject>

class WebSocketClient;

class NetworkApi : public QObject {
public:
    NetworkApi(WebSocketClient* webSocketClient, QObject* parent = nullptr);

private:
    WebSocketClient* m_webSocketClient = nullptr;
};
