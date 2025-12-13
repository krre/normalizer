#pragma once
#include <QObject>

class WebSocketClient;

namespace Api {

class Network : public QObject {
public:
    Network(WebSocketClient* webSocketClient, QObject* parent = nullptr);

    void sendMessage(const QByteArray& message);

private:
    WebSocketClient* m_webSocketClient = nullptr;
};

}
