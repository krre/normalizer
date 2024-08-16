#include "NetworkAccessManager.h"
#include <QNetworkReply>

namespace Async {

NetworkWaker::NetworkWaker(QNetworkReply* reply) {
    QObject::connect(reply, &QNetworkReply::finished, [this, reply] {
        reply->deleteLater();
        awaiter()->resume(reply);
    });

    QObject::connect(reply, &QNetworkReply::sslErrors, [] (const QList<QSslError>& errors) {
        for (auto& error : errors) {
            if (error.error() == QSslError::SelfSignedCertificate || error.error() == QSslError::HostNameMismatch) {
                continue;
            }

            qWarning() << "SSL error:" << error.errorString();
        }
    });

    reply->ignoreSslErrors();
}

Awaiter<QNetworkReply*> NetworkAccessManager::get(const QNetworkRequest& request) {
    return Awaiter<QNetworkReply*>(std::make_unique<NetworkWaker>(m_networkAccessManager.get(request)));
}

Awaiter<QNetworkReply*> NetworkAccessManager::post(const QNetworkRequest& request, const QByteArray& data) {
    return Awaiter<QNetworkReply*>(std::make_unique<NetworkWaker>(m_networkAccessManager.post(request, data)));
}

Awaiter<QNetworkReply*> NetworkAccessManager::put(const QNetworkRequest& request, const QByteArray& data) {
    return Awaiter<QNetworkReply*>(std::make_unique<NetworkWaker>(m_networkAccessManager.put(request, data)));
}

Awaiter<QNetworkReply*> NetworkAccessManager::deleteResource(const QNetworkRequest& request) {
    return Awaiter<QNetworkReply*>(std::make_unique<NetworkWaker>(m_networkAccessManager.deleteResource(request)));
}

}
