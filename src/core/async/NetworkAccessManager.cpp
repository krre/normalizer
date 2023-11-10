#include "NetworkAccessManager.h"
#include <QNetworkReply>

namespace Async {

NetworkWaker::NetworkWaker(QNetworkReply* reply) {
    QObject::connect(reply, &QNetworkReply::finished, [this, reply] {
        reply->deleteLater();
        awaiter()->resume(reply);
    });
}

Awaiter<QNetworkReply*> NetworkAccessManager::get(const QNetworkRequest& request) {
    return Awaiter<QNetworkReply*>(std::make_unique<NetworkWaker>(m_networkAccessManager.get(request)));
}

Awaiter<QNetworkReply*> NetworkAccessManager::post(const QNetworkRequest& request, const QByteArray& data) {
    return Awaiter<QNetworkReply*>(std::make_unique<NetworkWaker>(m_networkAccessManager.post(request, data)));
}

}
