#include "WebSocketClient.h"
#include <QWebSocket>

WebSocketClient::WebSocketClient(const QUrl& url, QObject* parent) : QObject(parent), m_url(url) {
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
    m_webSocket->open(m_url);
}

WebSocketClient::State WebSocketClient::state() const {
    return m_webSocket->state() == QAbstractSocket::ConnectedState ? State::Connected : State::Disconnected;
}
