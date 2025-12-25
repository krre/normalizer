#include "Network.h"
#include "core/async/Awaiter.h"
#include <QWebSocket>

NetworkWaker::NetworkWaker(QWebSocket* webSocket) {
    QObject::connect(webSocket, &QWebSocket::binaryMessageReceived, [this] (const QByteArray& message) {
        awaiter()->resume(message);
    });
}

Network::Network(const QUrl& url, QObject* parent) : QObject(parent), m_url(url) {
    m_webSocket = new QWebSocket;
    m_webSocket->setParent(this);

    QObject::connect(m_webSocket, &QWebSocket::connected, this, [this] {
        setState(State::Connected);
    });

    QObject::connect(m_webSocket, &QWebSocket::disconnected, this, [this] {
        setState(State::Disconnected);
    });
}

Async::Awaiter<QByteArray> Network::sendMessage(const QByteArray& message) {
    m_webSocket->sendBinaryMessage(message);
    return Async::Awaiter<QByteArray>(std::make_unique<NetworkWaker>(m_webSocket));
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
