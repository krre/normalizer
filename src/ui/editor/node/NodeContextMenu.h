#pragma once
#include <QMenu>

class NodeContextMenu : public QMenu {
    Q_OBJECT
public:
    NodeContextMenu(QWidget* parent);

signals:
    void addModule();
};
