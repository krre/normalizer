#include "Space3d.h"
#include <QtWidgets>
#include <Qt3DExtras>

Space3d::Space3d(NodeManager* nodeManager, Id projectId) : m_nodeManager(nodeManager), m_projectId(projectId) {
    Qt3DExtras::Qt3DWindow* view = new Qt3DExtras::Qt3DWindow();
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    view->renderSettings()->setRenderPolicy(Qt3DRender::QRenderSettings::OnDemand);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(QWidget::createWindowContainer(view));
}
