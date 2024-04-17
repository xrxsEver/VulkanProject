#pragma once

#include "vulkanbase/VulkanBase.h"
#include <Vertex.h>

class xrxsPipeline {
public:
    void initialize(VkDevice device);
    void recordCommands(VkCommandBuffer commandBuffer);

private:
    void createGraphicsPipeline(VkDevice device);
    void createShaderModules();

    void drawScene(VkCommandBuffer commandBuffer);
    VkPushConstantRange createPushConstantRange();

    // Vulkan handles and objects
    VkPipeline m_Pipeline;
    VkShaderModule m_VertexShaderModule;
    VkShaderModule m_FragmentShaderModule;
    VkPipelineLayout m_PipelineLayout;
    VkDescriptorSetLayout m_DescriptorSetLayout;
    VkDescriptorPool m_DescriptorPool;
    VkDescriptorSet m_DescriptorSet;
    std::vector<VkFramebuffer> m_Framebuffers;
    std::vector<VkCommandBuffer> m_CommandBuffers;

    // Swap chain details, could be part of a struct or individual members
    VkSwapchainKHR m_SwapChain;
    std::vector<VkImage> m_SwapChainImages;
    VkFormat m_SwapChainImageFormat;
    VkExtent2D m_SwapChainExtent;

    
    CommandBuffer m_Buffer;
    VkPipeline graphicsPipeline;
    VkPipelineLayout pipelineLayout;
    std::unique_ptr<Shader2D> m_pShader;


    // Meshes and other renderable objects
    std::vector<MeshData> m_Meshes;

};