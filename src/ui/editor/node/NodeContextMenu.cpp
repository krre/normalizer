#include "NodeContextMenu.h"

NodeContextMenu::NodeContextMenu(QWidget* parent) : QMenu(parent) {
    setAttribute(Qt::WA_DeleteOnClose);
    addMenu(tr("Add"));
    addAction(tr("Remove..."));
}
