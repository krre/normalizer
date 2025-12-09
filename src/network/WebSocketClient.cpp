#include "WebSocketClient.h"
#include <QWebSocket>

WebSocketClient::WebSocketClient(int port, QObject* parent) : QObject(parent), m_port(port) {
    m_webSocket = new QWebSocket;
    m_webSocket->setParent(this);

    QObject::connect(m_webSocket, &QWebSocket::connected, this, [this] {
        emit stateChanged(State::Connected);
    });

    QObject::connect(m_webSocket, &QWebSocket::disconnected, this, [this] {
        emit stateChanged(State::Disconnected);
    });

    QObject::connect(m_webSocket, &QWebSocket::binaryMessageReceived, this, [this] (const QByteArray& message) {
        emit messageReceived(message);
    });
}

void WebSocketClient::connect() {
    m_webSocket->open(QUrl(QString("ws://127.0.0.1:%1").arg(m_port)));
}
