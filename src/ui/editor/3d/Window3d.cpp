#include "Window3d.h"
#include "View3dContextMenu.h"
#include <QMenu>
#include <QMouseEvent>

Window3d::Window3d() {}

void Window3d::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        View3dContextMenu menu;
        QAction* action = menu.exec(event->globalPosition().toPoint());
        auto menuAction = action->data().value<View3dContextMenu::Action>();

        if (menuAction == View3dContextMenu::Action::AddModule) {
            qDebug() << "Add module";
        }
    } else {
        Qt3DExtras::Qt3DWindow::mousePressEvent(event);
    }
}
