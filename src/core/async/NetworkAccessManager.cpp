#include "NetworkAccessManager.h"
#include <QJsonDocument>
#include <QNetworkReply>

namespace Async {

NetworkWaker::NetworkWaker(QNetworkReply* reply) {
    QObject::connect(reply, &QNetworkReply::finished, [this, reply] {
        reply->deleteLater();

        if (reply->error() == QNetworkReply::NoError) {
            awaiter()->resume(reply->readAll());
        }
    });

    QObject::connect(reply, &QNetworkReply::errorOccurred, [reply] (QNetworkReply::NetworkError code) {
        qCritical() << "error" << code << reply->errorString();
    });
}

Awaiter<QByteArray> NetworkAccessManager::post(const QNetworkRequest& request, const QByteArray& data) {
    return Awaiter<QByteArray>(std::make_unique<NetworkWaker>(m_networkAccessManager.post(request, data)));
}

}
