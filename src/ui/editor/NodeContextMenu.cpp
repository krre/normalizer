#include "NodeContextMenu.h"
#include "NodeManager.h"

NodeContextMenu::NodeContextMenu(NodeManager* nodeManager, QWidget* parent) : QMenu(parent) {
    QMenu* addMenu = QMenu::addMenu(tr("Add"));

    QAction* action = new QAction(tr("Module"), this);
    action->setData(QVariant::fromValue(Action::AddModule));
    connect(action, &QAction::triggered, this, [=] {
        nodeManager->createModule();
    });

    addMenu->addAction(action);
}
