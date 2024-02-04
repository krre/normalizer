#include "NodeTreeView.h"
#include "ui/editor/NodeContextMenu.h"
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
    auto contextMenu = new NodeContextMenu(m_nodeManager, this);
    contextMenu->exec(mapToGlobal(point));
}

Async::Task<void> NodeTreeView::addModule() {
    co_await m_nodeManager->createModule();
}
