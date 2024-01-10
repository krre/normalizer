#pragma once
#include <QMenu>

class NodeContextMenu : public QMenu {
public:
    NodeContextMenu(QWidget* parent);

private slots:
    void addModule();
};
