#include "RenderView.h"
#include <QtWidgets>

RenderView::RenderView(Id projectId) {
    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);

    setVisible(false);
}
