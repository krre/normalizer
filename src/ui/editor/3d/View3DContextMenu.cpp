#include "View3DContextMenu.h"

View3DContextMenu::View3DContextMenu(QWidget* parent) : QMenu(parent) {
    QMenu* addMenu = QMenu::addMenu(tr("Add"));

    QAction* action = new QAction(tr("Module"), this);
    action->setData(QVariant::fromValue(Action::AddModule));

    addMenu->addAction(action);
}
