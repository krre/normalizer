#pragma once
#include "Task.h"
#include <QNetworkAccessManager>

namespace Async {

class NetworkWaker : public Waker<QByteArray> {
public:
    NetworkWaker(QNetworkReply* reply);
};

class NetworkAccessManager {
public:
    NetworkAccessManager() = default;
    Awaiter<QByteArray> post(const QNetworkRequest& request, const QByteArray& data);

private:
    QNetworkAccessManager m_networkAccessManager;
};

}
