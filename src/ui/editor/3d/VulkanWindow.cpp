#include "VulkanWindow.h"
#include "VulkanRenderer.h"
#include "external/settings/FileSettings.h"

VulkanWindow::VulkanWindow(QVulkanInstance* instance) {
    setVulkanInstance(instance);

    FileSettings settings;
    setPhysicalDeviceIndex(settings.graphics().adapter);
}

QVulkanWindowRenderer* VulkanWindow::createRenderer() {
    return new VulkanRenderer(this);
}
