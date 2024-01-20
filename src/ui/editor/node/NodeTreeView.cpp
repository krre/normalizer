#include "NodeTreeView.h"
#include "NodeContextMenu.h"
#include "ui/editor/NodeManager.h"
#include "ui/editor/model/NodeModel.h"
#include <QtWidgets>

NodeTreeView::NodeTreeView(NodeManager* nodeManager) : m_nodeManager(nodeManager) {
    setModel(nodeManager->model());
    header()->setVisible(false);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTreeWidget::customContextMenuRequested, this, &NodeTreeView::showContextMenu);
}

void NodeTreeView::showContextMenu(const QPoint& point) {
    auto contextMenu = new NodeContextMenu(this);
    connect(contextMenu, &NodeContextMenu::addModule, this, &NodeTreeView::addModule);

    contextMenu->exec(mapToGlobal(point));
}

void NodeTreeView::addModule() {
    qDebug() << "add module";
}
