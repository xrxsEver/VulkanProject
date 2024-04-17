#pragma once

#include <GLFW/glfw3.h>
#include "VulkanUtil.h"
#include "Shader2D.h"
#include "xrxsPipeline.h"
#include "DAEMesh.h"
#include "command/CommandPool.h"
#include "Command/CommandBuffer.h"

class VulkanBase {
public:
    VulkanBase();
    ~VulkanBase();
    void run();

private:
    void initWindow();
    void initVulkan();
    void mainLoop();
    void cleanup();

    void createInstance();
    void setupDebugMessenger();
    void createSurface();
    void pickPhysicalDevice();
    void createLogicalDevice();
    void createSwapChain();
    void createImageViews();
    void createRenderPass();
    void createGraphicsPipeline();
    void createFrameBuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void drawFrame();

    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;
    std::vector<VkImage> swapChainImages;
    std::vector<VkImageView> swapChainImageViews;
    std::vector<VkFramebuffer> swapChainFramebuffers;
    VkRenderPass renderPass;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipelineLayout pipelineLayout;
    VkPipeline graphicsPipeline;
    VkCommandPool commandPool;
    std::vector<VkCommandBuffer> commandBuffers;
    std::vector<VkSemaphore> imageAvailableSemaphores;
    std::vector<VkSemaphore> renderFinishedSemaphores;
    std::vector<VkFence> inFlightFences;
    size_t currentFrame = 0;

    bool framebufferResized = false;

    VkDebugUtilsMessengerEXT debugMessenger;
    std::unique_ptr<Shader2D> m_GradientShader;
    std::unique_ptr<CommandPool> m_CommandPool;
    std::unique_ptr<xrxsPipeline> m_Pipeline;
    std::unique_ptr<DAEMesh> m_Mesh;

    void createVertexBuffer();
    void createIndexBuffer();

    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
};
