#include "CommandPool.h"

void CommandPool::initialize(const VkDevice& device, const QueueFamilyIndices& queue) {
    m_VkDevice = device;

    VkCommandPoolCreateInfo poolInfo{};
    poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    poolInfo.queueFamilyIndex = queue.graphicsFamily.value();
    poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

    if (vkCreateCommandPool(device, &poolInfo, nullptr, &m_CommandPool) != VK_SUCCESS) {
        throw std::runtime_error("failed to create command pool!");
    }
}

void CommandPool::destroy() {
    if (m_CommandPool != VK_NULL_HANDLE) {
        vkDestroyCommandPool(m_VkDevice, m_CommandPool, nullptr);
        m_CommandPool = VK_NULL_HANDLE;
    }
}

CommandBuffer CommandPool::createCommandBuffer() const {
    CommandBuffer commandBuffer;

    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = m_CommandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(m_VkDevice, &allocInfo, &commandBuffer.getVkCommandBuffer()) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffers!");
    }

    return commandBuffer;

}
