#pragma once
#include "Handle.h"
#include <vector>
#include <memory>

class QVulkanInstance;
class QVulkanFunctions;

namespace Vulkan {

class PhysicalDevice;

class Instance : public Handle<VkInstance> {
public:
    Instance(QVulkanInstance* instance);

    std::vector<std::unique_ptr<PhysicalDevice>> createPhysicalDevices() const;

private:
    QVulkanFunctions* m_funcs = nullptr;
};

}
