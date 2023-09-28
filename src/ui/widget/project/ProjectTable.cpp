#include "ProjectTable.h"
#include "core/Settings.h"
#include <QtNetwork>

ProjectTable::ProjectTable() {
    setColumnCount(5);
    setHorizontalHeaderLabels({ tr("Name"), tr("Template"), tr("Description"), tr("Created time"), tr("Updated time") });
    setSelectionBehavior(QAbstractItemView::SelectItems);
    networkAccessManager.reset(new QNetworkAccessManager);

    load();
}

void ProjectTable::load() {
    QString host = Settings::value<Server::Host>();
    quint64 port = Settings::value<Server::Port>();

    QNetworkRequest request(QUrl(QString("http://%1:%2/projects").arg(host).arg(port)));
    QNetworkReply* reply = networkAccessManager->get(request);

    connect(reply, &QNetworkReply::finished, [=] {
        reply->deleteLater();
    });

    connect(reply, &QNetworkReply::errorOccurred, [=] (QNetworkReply::NetworkError code) {
        qWarning().noquote() << code;
    });

    connect(reply, &QNetworkReply::readyRead, [=] {
        qDebug() << reply->readAll();
    });
}
