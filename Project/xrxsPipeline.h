#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include "Shader2D.h"
#include "Command/CommandBuffer.h"

class xrxsPipeline {
public:
    void initialize(VkDevice device, Shader2D& shader2D);
    void recordCommands(VkCommandBuffer commandBuffer);
    void drawScene(VkCommandBuffer commandBuffer);

private:
    void createGraphicsPipeline(VkDevice device, Shader2D& shader2D);
    VkPushConstantRange createPushConstantRange();

    VkPipeline m_Pipeline;
    VkPipelineLayout m_PipelineLayout;

    std::vector<VkFramebuffer> m_Framebuffers;
    std::vector<VkCommandBuffer> m_CommandBuffers;
};
