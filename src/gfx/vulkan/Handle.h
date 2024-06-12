#pragma once
#include <vulkan/vulkan.h>
#include <assert.h>

namespace Vulkan {

template <typename T>
class Handle {
public:
    Handle(T handle) : m_handle(handle) {
        assert(handle != VK_NULL_HANDLE);
    }

    T handle() const { return m_handle; }

private:
    T m_handle = VK_NULL_HANDLE;
};

}
