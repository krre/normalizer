#include "Instance.h"
#include "device/PhysicalDevice.h"
#include <QVulkanInstance>
#include <QVulkanFunctions>

namespace Vulkan {

Instance::Instance(QVulkanInstance* instance) : Handle(instance->vkInstance()), m_funcs(instance->functions()) {

}

std::vector<std::unique_ptr<PhysicalDevice>> Instance::createPhysicalDevices() const {
    uint32_t count;
    m_funcs->vkEnumeratePhysicalDevices(handle(), &count, nullptr);
    std::vector<VkPhysicalDevice> handles(count);
    m_funcs->vkEnumeratePhysicalDevices(handle(), &count, handles.data());

    std::vector<std::unique_ptr<PhysicalDevice>> result;

    for (const auto& handle : handles) {
        result.push_back(std::make_unique<PhysicalDevice>(handle, m_funcs));
    }

    return result;
}

}
