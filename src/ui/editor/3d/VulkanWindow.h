#pragma once
#include <QVulkanWindow>

class VulkanWindow : public QVulkanWindow {
public:
    VulkanWindow();
    QVulkanWindowRenderer* createRenderer() override;
};
