#pragma once
#include <QObject>

class WebSocketClient;

namespace Api {

class ApiNetwork : public QObject {
public:
    ApiNetwork(WebSocketClient* webSocketClient, QObject* parent = nullptr);

private:
    WebSocketClient* m_webSocketClient = nullptr;
};

}
