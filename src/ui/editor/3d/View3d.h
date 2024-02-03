#pragma once
#include <QWidget>

class NodeManager;

class View3d : public QWidget {
public:
    View3d(NodeManager* nodeManager);

private:
    NodeManager* m_nodeManager = nullptr;
};
