#pragma once
#include <QObject>
#include <QUrl>

class QWebSocket;

class WebSocketClient : public QObject {
    Q_OBJECT
public:
    enum class State {
        Connecting,
        Connected,
        Disconnected
    };

    WebSocketClient(const QUrl& url, QObject* parent = nullptr);

    void connect();
    State state() const;

signals:
    void stateChanged(WebSocketClient::State state);
    void messageReceived(const QByteArray& message);

private:
    void setState(State state);

    QWebSocket* m_webSocket = nullptr;
    QUrl m_url;
    State m_state = State::Disconnected;
};
