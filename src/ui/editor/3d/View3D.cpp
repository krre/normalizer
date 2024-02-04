#include "View3D.h"
#include "Window3D.h"
#include <QtWidgets>
#include <Qt3DExtras>

View3D::View3D(NodeManager* nodeManager) : m_nodeManager(nodeManager) {
    auto view = new Window3D;
    view->defaultFrameGraph()->setClearColor(QColor(QRgb(0x4d4d4f)));
    view->renderSettings()->setRenderPolicy(Qt3DRender::QRenderSettings::OnDemand);

    auto layout = new QVBoxLayout(this);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->addWidget(QWidget::createWindowContainer(view));
}
