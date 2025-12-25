#pragma once
#include "core/async/Awaiter.h"
#include <QObject>

class WebSocketClient;

class NetworkWaker : public Async::Waker<QByteArray> {
public:
    NetworkWaker(WebSocketClient* webSocketClient);
};

class Network : public QObject {
public:
    Network(WebSocketClient* webSocketClient, QObject* parent = nullptr);

    Async::Awaiter<QByteArray> sendMessage(const QByteArray& message);

private:
    WebSocketClient* m_webSocketClient = nullptr;
};
