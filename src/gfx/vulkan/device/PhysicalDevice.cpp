#include "PhysicalDevice.h"
#include <QVulkanFunctions>

namespace Vulkan {

PhysicalDevice::PhysicalDevice(VkPhysicalDevice handle, QVulkanFunctions* funcs) : Handle(handle), m_funcs(funcs) {

}

VkPhysicalDeviceProperties PhysicalDevice::properties() const {
    VkPhysicalDeviceProperties result;
    m_funcs->vkGetPhysicalDeviceProperties(handle(), &result);
    return result;
}

}
