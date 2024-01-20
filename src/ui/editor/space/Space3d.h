#pragma once
#include <core/CommonTypes.h>
#include <QWidget>

class NodeManager;

class Space3d : public QWidget {
public:
    Space3d(NodeManager* nodeManager, Id projectId);

private:
    NodeManager* m_nodeManager = nullptr;
    Id m_projectId;
};
