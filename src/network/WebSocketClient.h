#pragma once
#include <QObject>

class QWebSocket;

class WebSocketClient : public QObject {
    Q_OBJECT
public:
    enum class State {
        Connected,
        Disconnected
    };

    WebSocketClient(int port, QObject* parent = nullptr);

    void connect();
    State state() const;

signals:
    void stateChanged(WebSocketClient::State state);
    void messageReceived(const QByteArray& message);

private:
    QWebSocket* m_webSocket = nullptr;
    int m_port = 0;
};
