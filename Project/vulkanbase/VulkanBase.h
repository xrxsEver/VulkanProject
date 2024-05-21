#pragma once

#include <vulkan/vulkan.h>
#include <memory>
#include "VulkanUtil.h"

class Shader2D;
class xrxsPipeline;
class DAEMesh;
class CommandPool;
class CommandBuffer;
class SwapChainManager;



extern const std::vector<const char*> validationLayers;
extern std::vector<const char*> deviceExtensions;

const int MAX_FRAMES_IN_FLIGHT = 2;

// VulkanBase class with necessary Vulkan objects and methods
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
    void initializeShaders();
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

    void initializeUBO();

    GLFWwindow* window;
    VkInstance instance;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkSurfaceKHR surface;
    VkSwapchainKHR swapChain;
    std::unique_ptr<SwapChainManager> swapChainManager;

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
    bool checkValidationLayerSupport();

    VkDebugUtilsMessengerEXT debugMessenger;
    std::unique_ptr<Shader2D> shader2D;
    std::unique_ptr<CommandPool> m_CommandPool;
    std::unique_ptr<xrxsPipeline> m_Pipeline;

    std::unique_ptr<DAEMesh> m_Mesh;
    CommandBuffer* m_CommandBuffer;

    void createVertexBuffer();
    void createIndexBuffer();
    void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
    std::vector<const char*> getRequiredExtensions();
    bool checkDeviceExtensionSupport(VkPhysicalDevice device);
};
