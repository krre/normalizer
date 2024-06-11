#include "VulkanWindow.h"
#include "VulkanRenderer.h"

VulkanWindow::VulkanWindow(QVulkanInstance* instance) {
    setVulkanInstance(instance);
    setPhysicalDeviceIndex(1);
}

QVulkanWindowRenderer* VulkanWindow::createRenderer() {
    return new VulkanRenderer(this);
}
