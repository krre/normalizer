#include "Space3d.h"
#include <QtWidgets>
#include <QWebEngineView>

Space3d::Space3d(const QUrl& webUrl, Id projectId) : m_projectId(projectId) {
    QWebEngineView* view = new QWebEngineView;
    view->load(QString("%1/editor/%2").arg(webUrl.toString()).arg(projectId));

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
}
