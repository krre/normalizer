#pragma once
#include <QTreeView>

class NodeManager;

class NodeTreeView : public QTreeView {
public:
    NodeTreeView(NodeManager* nodeManager);

private slots:
    void showContextMenu(const QPoint& point);
    void addModule();

private:
    NodeManager* m_nodeManager = nullptr;
};
