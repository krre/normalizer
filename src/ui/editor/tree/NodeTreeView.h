#pragma once
#include "core/async/Task.h"
#include <QTreeView>

class NodeManager;

class NodeTreeView : public QTreeView {
public:
    NodeTreeView(NodeManager* nodeManager);

private slots:
    void showContextMenu(const QPoint& point);
    Async::Task<void> addModule();

private:
    NodeManager* m_nodeManager = nullptr;
};
