#pragma once

#include <vulkan/vulkan.h>

class CommandBuffer {
public:
    CommandBuffer(VkDevice device, VkCommandPool commandPool);
    ~CommandBuffer();

    void allocate();
    VkCommandBuffer getCommandBuffer() const;

private:
    VkDevice device;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;
};
