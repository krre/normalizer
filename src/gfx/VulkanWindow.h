#pragma once
#include <QVulkanWindow>

class VulkanWindow : public QVulkanWindow {
public:
    VulkanWindow(QVulkanInstance* instance);
    QVulkanWindowRenderer* createRenderer() override;
};
