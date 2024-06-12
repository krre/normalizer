#include "View3D.h"
#include "gfx/VulkanWindow.h"
#include <QtWidgets>

View3D::View3D(VulkanWindow* vulkanWindow, NodeManager* nodeManager) : m_nodeManager(nodeManager) {
    auto wrapper = QWidget::createWindowContainer(vulkanWindow);

    auto verticalLayout = new QVBoxLayout;
    verticalLayout->setContentsMargins(QMargins());
    verticalLayout->addWidget(wrapper);

    setLayout(verticalLayout);
}
