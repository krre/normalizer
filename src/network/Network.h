#pragma once
#include "core/async/Awaiter.h"
#include <QObject>
#include <QUrl>

class QWebSocket;

using WebSocketAwaiter = Async::Awaiter<QByteArray>;

class Network : public QObject {
    Q_OBJECT
public:
    enum class State {
        Connecting,
        Connected,
        Disconnected
    };

    Network(const QUrl& url, QObject* parent = nullptr);

    void connect();
    State state() const;

    QScopedPointer<WebSocketAwaiter> sendMessage(const QByteArray& message);

signals:
    void stateChanged(Network::State state);

private:
    void setState(State state);

    QWebSocket* m_webSocket = nullptr;
    QUrl m_url;
    State m_state = State::Disconnected;
    WebSocketAwaiter* m_awaiter = nullptr;
};
