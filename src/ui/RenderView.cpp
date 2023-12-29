#include "RenderView.h"
#include <QtWidgets>
#include <QWebEngineView>

RenderView::RenderView(const QUrl& editorUrl, Id projectId) {
    QWebEngineView* view = new QWebEngineView;
    view->load(editorUrl);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(view);
}
