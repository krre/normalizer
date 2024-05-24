#pragma once
#include <QWidget>

class VulkanWindow;
class NodeManager;

class View3D : public QWidget {
public:
    View3D(VulkanWindow* vulkanWindow, NodeManager* nodeManager);

private:
    NodeManager* m_nodeManager = nullptr;
};
