#include "CommandBuffer.h"
#include <stdexcept>

CommandBuffer::CommandBuffer()
{
    allocateCommandBuffer();
}

CommandBuffer::~CommandBuffer() {
    vkFreeCommandBuffers(m_Device, m_CommandPool, 1, &m_CommandBuffer);
}

void CommandBuffer::setVkCommandBuffer(VkCommandBuffer buffer) {
    m_CommandBuffer = buffer;
}

VkCommandBuffer CommandBuffer::getVkCommandBuffer() const {
    return m_CommandBuffer;
}

void CommandBuffer::reset() {
    vkResetCommandBuffer(m_CommandBuffer, 0);
}

void CommandBuffer::beginRecording() {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

    if (vkBeginCommandBuffer(m_CommandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }
}

void CommandBuffer::endRecording() {
    if (vkEndCommandBuffer(m_CommandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void CommandBuffer::submit(VkSubmitInfo& submitInfo, VkQueue graphicsQueue, VkFence fence) {
    if (vkQueueSubmit(graphicsQueue, 1, &submitInfo, fence) != VK_SUCCESS) {
        throw std::runtime_error("failed to submit draw command buffer!");
    }
}

void CommandBuffer::allocateCommandBuffer() {
    VkCommandBufferAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.commandPool = m_CommandPool;
    allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
    allocInfo.commandBufferCount = 1;

    if (vkAllocateCommandBuffers(m_Device, &allocInfo, &m_CommandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to allocate command buffer!");
    }
}
