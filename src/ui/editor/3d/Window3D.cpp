#include "Window3D.h"
#include "View3DContextMenu.h"
#include <QMenu>
#include <QMouseEvent>

Window3D::Window3D() {}

void Window3D::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::RightButton) {
        View3DContextMenu menu;
        QAction* action = menu.exec(event->globalPosition().toPoint());

        if (!action) return;

        auto menuAction = action->data().value<View3DContextMenu::Action>();

        if (menuAction == View3DContextMenu::Action::AddModule) {
            qDebug() << "Add module";
        }
    } else {
        Qt3DExtras::Qt3DWindow::mousePressEvent(event);
    }
}
