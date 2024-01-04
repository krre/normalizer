#include "RenderView.h"
#include <QtWidgets>
#include <QWebEngineView>

RenderView::RenderView(const QUrl& webUrl, Id projectId) : m_projectId(projectId) {
    QWebEngineView* view = new QWebEngineView;
    view->load(QString("%1/editor/%2").arg(webUrl.toString()).arg(projectId));

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
}
