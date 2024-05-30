#include "VulkanWindow.h"
#include "VulkanRenderer.h"

VulkanWindow::VulkanWindow() {

}

QVulkanWindowRenderer* VulkanWindow::createRenderer() {
    return new VulkanRenderer(this);
}
