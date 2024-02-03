#include "View3d.h"
#include "Window3d.h"
#include <QtWidgets>
#include <Qt3DExtras>

View3d::View3d(NodeManager* nodeManager) : m_nodeManager(nodeManager) {
    auto view = new Window3d;
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    view->renderSettings()->setRenderPolicy(Qt3DRender::QRenderSettings::OnDemand);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(QWidget::createWindowContainer(view));
}
