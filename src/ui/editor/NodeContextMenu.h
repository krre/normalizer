#pragma once
#include <QMenu>

class NodeManager;

class NodeContextMenu : public QMenu {
    Q_OBJECT
public:
    enum class Action {
        AddModule
    };

    NodeContextMenu(NodeManager* nodeManager, QWidget* parent = nullptr);
};
