#pragma once
#include <QVulkanWindowRenderer>

class VulkanRenderer : public QVulkanWindowRenderer {
public:
    VulkanRenderer();
    void startNextFrame() override;
};
