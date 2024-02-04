#include "Window3D.h"
#include "ui/editor/NodeContextMenu.h"
#include <QMenu>
#include <QMouseEvent>

Window3D::Window3D(NodeManager* nodeManager) : m_nodeManager(nodeManager) {}

void Window3D::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        NodeContextMenu menu(m_nodeManager);
        QAction* action = menu.exec(event->globalPosition().toPoint());

        if (!action) return;

        auto menuAction = action->data().value<NodeContextMenu::Action>();

        if (menuAction == NodeContextMenu::Action::AddModule) {
            qDebug() << "Add module";
        }
    } else {
        Qt3DExtras::Qt3DWindow::mousePressEvent(event);
    }
}
