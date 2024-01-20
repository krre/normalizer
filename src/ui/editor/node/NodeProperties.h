#pragma once
#include <QWidget>

class NodeManager;

class NodeProperties : public QWidget {
    Q_OBJECT
public:
    NodeProperties(NodeManager* nodeManager, QWidget* parent = nullptr);

private:
    NodeManager* m_nodeManager = nullptr;
};
