#pragma once
#include "vulkan/vulkan_core.h"

class CommandBuffer {
public:
    // Constructor
    CommandBuffer() = default;

    // Setter and Getter for VkCommandBuffer
    void setVkCommandBuffer(VkCommandBuffer buffer) {
        m_CommandBuffer = buffer;
    }

    VkCommandBuffer getVkCommandBuffer() const {
        return m_CommandBuffer;
    }

    // Methods for command buffer operations
    void reset();
    void beginRecording();
    void endRecording();
    void submit(VkSubmitInfo& info);

private:
    VkCommandBuffer m_CommandBuffer;
};
