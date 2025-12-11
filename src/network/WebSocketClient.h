#pragma once
#include <QObject>
#include <QUrl>

class QWebSocket;

class WebSocketClient : public QObject {
    Q_OBJECT
public:
    enum class State {
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
    QWebSocket* m_webSocket = nullptr;
    QUrl m_url;
};
