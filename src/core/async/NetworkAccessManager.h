#pragma once
#include "Awaiter.h"
#include <QNetworkAccessManager>

class QNetworkReply;

namespace Async {

class NetworkWaker : public Waker<QNetworkReply*> {
public:
    NetworkWaker(QNetworkReply* reply);
};

class NetworkAccessManager {
public:
    NetworkAccessManager() = default;

    Awaiter<QNetworkReply*> get(const QNetworkRequest& request);
    Awaiter<QNetworkReply*> post(const QNetworkRequest& request, const QByteArray& data);
    Awaiter<QNetworkReply*> put(const QNetworkRequest& request, const QByteArray& data);
    Awaiter<QNetworkReply*> deleteResource(const QNetworkRequest& request);

private:
    QNetworkAccessManager m_networkAccessManager;
};

}
