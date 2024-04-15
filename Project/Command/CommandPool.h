#pragma once

 #include "vulkan/vulkan_core.h"
 #include "CommandBuffer.h"
 #include "vulkanbase/VulkanUtil.h"
 #include "vulkanbase/VulkanBase.h"


class CommandPool {
public:
    // Constructors
    CommandPool() : m_CommandPool(VK_NULL_HANDLE), m_VkDevice(VK_NULL_HANDLE) {}
    CommandPool(const CommandPool&) = default; // Copy constructor

    // Methods
    void initialize(const VkDevice& device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    void destroy();
    CommandBuffer createCommandBuffer() const;

private:
    VkCommandPool m_CommandPool;
    VkDevice m_VkDevice;
};