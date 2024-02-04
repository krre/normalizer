#pragma once
#include <QWidget>

class NodeManager;

class View3D : public QWidget {
public:
    View3D(NodeManager* nodeManager);

private:
    NodeManager* m_nodeManager = nullptr;
};
