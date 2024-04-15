#include "CommandBuffer.h"
#include <stdexcept>

void CommandBuffer::reset() {
    vkResetCommandBuffer(m_CommandBuffer, /*VkCommandBufferResetFlagBits*/ 0);
}

void CommandBuffer::beginRecording() {
    VkCommandBufferBeginInfo beginInfo{};
    beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo.flags = 0; // Optional
    beginInfo.pInheritanceInfo = nullptr; // Optional

    if (vkBeginCommandBuffer(m_CommandBuffer, &beginInfo) != VK_SUCCESS) {
        throw std::runtime_error("failed to begin recording command buffer!");
    }
}

void CommandBuffer::endRecording() {
    if (vkEndCommandBuffer(m_CommandBuffer) != VK_SUCCESS) {
        throw std::runtime_error("failed to record command buffer!");
    }
}

void CommandBuffer::submit(VkSubmitInfo& info) {
    info.commandBufferCount = 1;
    info.pCommandBuffers = &m_CommandBuffer;
}
