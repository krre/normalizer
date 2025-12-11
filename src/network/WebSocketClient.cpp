#include "WebSocketClient.h"
#include <QWebSocket>

WebSocketClient::WebSocketClient(const QUrl& url, QObject* parent) : QObject(parent), m_url(url) {
    m_webSocket = new QWebSocket;
    m_webSocket->setParent(this);

    QObject::connect(m_webSocket, &QWebSocket::connected, this, [this] {
        setState(State::Connected);
    });

    QObject::connect(m_webSocket, &QWebSocket::disconnected, this, [this] {
        setState(State::Disconnected);
    });

    QObject::connect(m_webSocket, &QWebSocket::binaryMessageReceived, this, [this] (const QByteArray& message) {
        emit messageReceived(message);
    });
}

void WebSocketClient::connect() {
    m_webSocket->open(m_url);
    setState(State::Connecting);
}

void WebSocketClient::setState(State state) {
    if (state == m_state) return;
    m_state = state;
    emit stateChanged(state);
}

WebSocketClient::State WebSocketClient::state() const {
    return m_state;
}
