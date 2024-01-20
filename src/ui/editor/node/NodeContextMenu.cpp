#include "NodeContextMenu.h"

NodeContextMenu::NodeContextMenu(QWidget* parent) : QMenu(parent) {
    setAttribute(Qt::WA_DeleteOnClose);

    QMenu* addMenu = QMenu::addMenu(tr("Add"));
    addMenu->addAction(tr("Module"), this, &NodeContextMenu::addModule);

    addAction(tr("Remove..."));
}
