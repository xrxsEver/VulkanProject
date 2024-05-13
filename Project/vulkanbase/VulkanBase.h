#pragma once

#include <GLFW/glfw3.h>
#include "VulkanUtil.h"
#include "Shader2D.h"
#include "xrxsPipeline.h"
#include "DAEMesh.h"
#include "command/CommandPool.h"
#include "Command/CommandBuffer.h"
#include "SwapChainManager.h"

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};
const int MAX_FRAMES_IN_FLIGHT = 2;  


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
    void createRenderPass();
    void createGraphicsPipeline();
    void createFrameBuffers();
    void createCommandPool();
    void createCommandBuffers();
    void createSyncObjects();
    void drawFrame();
    void drawScene();

    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;
    SwapChainManager swapChainManager;

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
    bool isDeviceSuitable(VkPhysicalDevice device);
    bool  checkValidationLayerSupport();

    VkDebugUtilsMessengerEXT debugMessenger;
    std::unique_ptr<Shader2D> m_GradientShader;
    std::unique_ptr<CommandPool> m_CommandPool;
    std::unique_ptr<xrxsPipeline> m_Pipeline;
    std::unique_ptr<DAEMesh> m_Mesh;

    void createVertexBuffer();
    void createIndexBuffer();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    std::vector<const char*> getRequiredExtensions();
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
};
