#include "CommandBuffer.h"

CommandBuffer::CommandBuffer(VkDevice device, VkCommandPool commandPool)
    : device(device), commandPool(commandPool), commandBuffer(VK_NULL_HANDLE) {}

CommandBuffer::~CommandBuffer() {
    if (commandBuffer != VK_NULL_HANDLE) {
        vkFreeCommandBuffers(device, commandPool, 1, &commandBuffer);
        commandBuffer = VK_NULL_HANDLE;
    }
}

void CommandBuffer::allocate() {
    // Implement your createCommandBuffer functionality here
}

VkCommandBuffer CommandBuffer::getCommandBuffer() const {
    return commandBuffer;
}