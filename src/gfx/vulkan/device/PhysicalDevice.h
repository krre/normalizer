#pragma once
#include "gfx/vulkan/Handle.h"

class QVulkanFunctions;

namespace Vulkan {

class PhysicalDevice : public Handle<VkPhysicalDevice> {
public:
    PhysicalDevice(VkPhysicalDevice handle, QVulkanFunctions* funcs);

    VkPhysicalDeviceProperties properties() const;

private:
    QVulkanFunctions* m_funcs = nullptr;
};

}
