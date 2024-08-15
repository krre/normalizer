#pragma once
#include <QWidget>

class VulkanWindow;
class Repository;

class View3D : public QWidget {
public:
    View3D(VulkanWindow* vulkanWindow, Repository* nodeManager);

private:
    Repository* m_nodeManager = nullptr;
};
