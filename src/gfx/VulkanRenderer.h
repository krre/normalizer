#pragma once
#include <QVulkanWindowRenderer>

class VulkanRenderer : public QVulkanWindowRenderer {
public:
    VulkanRenderer(QVulkanWindow* window);

    void initResources() override;
    void releaseResources() override;

    void startNextFrame() override;

private:
    QVulkanWindow* m_window = nullptr;
    QVulkanDeviceFunctions* m_devFuncs;
};
