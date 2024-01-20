#include "NodeTreeWidget.h"
#include "NodeContextMenu.h"
#include <QtWidgets>

NodeTreeWidget::NodeTreeWidget() {
    header()->setVisible(false);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, &QTreeWidget::customContextMenuRequested, this, &NodeTreeWidget::showContextMenu);
}

void NodeTreeWidget::showContextMenu(const QPoint& point) {
    auto contextMenu = new NodeContextMenu(this);
    connect(contextMenu, &NodeContextMenu::addModule, this, &NodeTreeWidget::addModule);

    contextMenu->exec(mapToGlobal(point));
}

void NodeTreeWidget::addModule() {
    qDebug() << "add module";
}
