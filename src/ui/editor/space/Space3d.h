#pragma once
#include <QWidget>

class NodeManager;

class Space3d : public QWidget {
public:
    Space3d(NodeManager* nodeManager);

private:
    NodeManager* m_nodeManager = nullptr;
};
