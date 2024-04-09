#include "CommandPool.h"

CommandPool::CommandPool(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface)
    : device(device), physicalDevice(physicalDevice), surface(surface), commandPool(VK_NULL_HANDLE) {}

CommandPool::~CommandPool() {
    if (commandPool != VK_NULL_HANDLE) {
        vkDestroyCommandPool(device, commandPool, nullptr);
        commandPool = VK_NULL_HANDLE;
    }
}

void CommandPool::create() {
    // Implement your createCommandPool functionality here
}

VkCommandPool CommandPool::getCommandPool() const {
    return commandPool;
}