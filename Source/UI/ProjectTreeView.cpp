#include "ProjectTreeView.h"
#include <QtWidgets>

ProjectTreeView::ProjectTreeView(QWidget* parent) : QTreeView(parent) {
    connect(this, &QTreeView::doubleClicked, this, &ProjectTreeView::onDoubleClicked);
    connect(this, &QTreeView::pressed, this, &ProjectTreeView::onMousePressed);

    _contextMenu = new QMenu(this);
    QAction* openAction = _contextMenu->addAction(tr("Open"));
    connect(openAction, &QAction::triggered, [=]() { openActivated(_selectedFile); });
    QAction* removeAction = _contextMenu->addAction(tr("Remove..."));
    connect(removeAction, &QAction::triggered, this, &ProjectTreeView::onFileRemove);
    QAction* renameAction = _contextMenu->addAction(tr("Rename..."));
    connect(renameAction, &QAction::triggered, this, &ProjectTreeView::onFileRename);
}

ProjectTreeView::~ProjectTreeView() {
}

void ProjectTreeView::onMousePressed(const QModelIndex& index) {
    if (QApplication::mouseButtons() == Qt::RightButton) {
        QFileInfo fi = qobject_cast<QFileSystemModel*>(model())->fileInfo(index);
        if (!fi.isDir()) {
            _selectedFile = fi.absoluteFilePath();
            _contextMenu->exec(QCursor::pos());
        }
    }
}

void ProjectTreeView::onDoubleClicked(const QModelIndex& index) {
    QFileInfo fi = qobject_cast<QFileSystemModel*>(model())->fileInfo(index);
    if (!fi.isDir() && fi.suffix() == "irbis") {
        openActivated(fi.absoluteFilePath());
    }
}

void ProjectTreeView::onFileRemove() {
    qDebug() << "Remove" << _selectedFile;
}

void ProjectTreeView::onFileRename() {
    qDebug() << "Rename" << _selectedFile;
}
