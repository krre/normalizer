#include "Network.h"
#include <QWebSocket>

Network::Network(const QUrl& url, QObject* parent) : QObject(parent), m_url(url) {
    m_webSocket = new QWebSocket;
    m_webSocket->setParent(this);

    QObject::connect(m_webSocket, &QWebSocket::connected, this, [this] {
        setState(State::Connected);
    });

    QObject::connect(m_webSocket, &QWebSocket::disconnected, this, [this] {
        setState(State::Disconnected);
    });

    QObject::connect(m_webSocket, &QWebSocket::binaryMessageReceived, [this] (const QByteArray& message) {
        if (m_awaiter) {
            m_awaiter->resume(message);
            m_awaiter = nullptr;
        }
    });
}

QScopedPointer<WebSocketAwaiter> Network::sendMessage(const QByteArray& message) {
    m_webSocket->sendBinaryMessage(message);
    m_awaiter = new WebSocketAwaiter;

    return QScopedPointer<WebSocketAwaiter>(m_awaiter);
}

void Network::connect() {
    m_webSocket->open(m_url);
    setState(State::Connecting);
}

void Network::setState(State state) {
    if (state == m_state) return;
    m_state = state;
    emit stateChanged(state);
}

Network::State Network::state() const {
    return m_state;
}
