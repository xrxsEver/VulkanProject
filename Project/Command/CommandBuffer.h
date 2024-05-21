#pragma once
#include "vulkan/vulkan_core.h"

class CommandBuffer {
public:
    // Constructor
    CommandBuffer();

    // Destructor
    ~CommandBuffer();

    // Setter and Getter for VkCommandBuffer
    void setVkCommandBuffer(VkCommandBuffer buffer);
    VkCommandBuffer getVkCommandBuffer() const;

    // Methods for command buffer operations
    void reset();
    void beginRecording();
    void endRecording();
    void submit(VkSubmitInfo& submitInfo, VkQueue graphicsQueue, VkFence fence = VK_NULL_HANDLE);

private:
    VkDevice m_Device;
    VkCommandPool m_CommandPool;
    VkCommandBuffer m_CommandBuffer;

    void allocateCommandBuffer();
};
