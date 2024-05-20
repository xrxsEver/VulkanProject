#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include "Shader2D.h"
#include "Command/CommandBuffer.h"


class xrxsPipeline {
public:
    xrxsPipeline();
    ~xrxsPipeline();

      

    void initialize(VkPhysicalDevice physicalDevice, VkDevice device, VkRenderPass renderPass, Shader2D& shader2D); // Include renderPass
    void recordCommands(VkCommandBuffer commandBuffer);
    void drawScene(VkCommandBuffer commandBuffer);

private:
    void createGraphicsPipeline(VkDevice device, VkRenderPass renderPass, Shader2D& shader2D); // Include renderPass
    VkPushConstantRange createPushConstantRange();

    VkPipeline m_Pipeline;
    VkPipelineLayout m_PipelineLayout;

    std::vector<VkFramebuffer> m_Framebuffers;
    std::vector<VkCommandBuffer> m_CommandBuffers;
};
