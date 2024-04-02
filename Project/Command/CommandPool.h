#pragma once

 #include "vulkan/vulkan_core.h"
 #include "CommandBuffer.h"
 #include "vulkanbase/VulkanUtil.h"

 class CommandPool
 {
 public:CommandPool():
 m_CommandPool{ VK_NULL_HANDLE },
 m_VkDevice{ VK_NULL_HANDLE }
 {

 }

 CommandPool() = default;

 void initialize(const VkDevice & device, const QueueFamilyIndices & queue);
 void destroy();

 CommandBuffer createCommandBuffer()const;
private:
 VkCommandPool m_CommandPool;
 VkDevice m_VkDevice;
 };