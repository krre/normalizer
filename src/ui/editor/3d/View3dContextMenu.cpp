#include "View3dContextMenu.h"

View3dContextMenu::View3dContextMenu(QWidget* parent) : QMenu(parent) {
    QMenu* addMenu = QMenu::addMenu(tr("Add"));

    QAction* action = new QAction(tr("Module"), this);
    action->setData(QVariant::fromValue(Action::AddModule));

    addMenu->addAction(action);
}
