#include "NodeTreeView.h"
#include "NodeContextMenu.h"
#include <QtWidgets>

NodeTreeView::NodeTreeView() {
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
