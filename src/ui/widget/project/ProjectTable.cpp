#include "ProjectTable.h"
#include "core/Settings.h"
#include <QtWidgets>
#include <QtNetwork>

ProjectTable::ProjectTable() {
    auto toolBar = new QToolBar;

    toolBar->addAction(tr("Add"), this, &ProjectTable::addProject);
    toolBar->addAction(tr("Edit"), this, &ProjectTable::editProject);
    toolBar->addAction(tr("Delete"), this, &ProjectTable::deleteProject);

    m_tableWidget = new QTableWidget;
    m_tableWidget->setColumnCount(5);
    m_tableWidget->setHorizontalHeaderLabels({ tr("Name"), tr("Template"), tr("Description"), tr("Created time"), tr("Updated time") });
    m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(0, 0, 0, 0);
    verticalLayout->addWidget(toolBar);
    verticalLayout->addWidget(m_tableWidget);

    setLayout(verticalLayout);

    networkAccessManager.reset(new QNetworkAccessManager);

    load();
}

void ProjectTable::addProject() {

}

void ProjectTable::editProject() {

}

void ProjectTable::deleteProject() {

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
