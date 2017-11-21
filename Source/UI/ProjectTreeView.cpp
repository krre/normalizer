#include "ProjectTreeView.h"
#include <QtWidgets>

ProjectTreeView::ProjectTreeView(QWidget* parent) : QTreeView(parent) {
    connect(this, &QTreeView::pressed, this, &ProjectTreeView::onMousePressed);

    contextMenu = new QMenu(this);
    contextMenu->addAction(tr("Open"));
    contextMenu->addAction(tr("Remove..."));
    contextMenu->addAction(tr("Rename..."));
}

ProjectTreeView::~ProjectTreeView() {
}

void ProjectTreeView::onMousePressed(const QModelIndex& index) {
    if (QApplication::mouseButtons() == Qt::RightButton) {
        QFileInfo fi = qobject_cast<QFileSystemModel*>(model())->fileInfo(index);
        if (!fi.isDir()) {
            contextMenu->exec(QCursor::pos());
        }
    }
}
