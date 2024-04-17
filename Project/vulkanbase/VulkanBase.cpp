#include "VulkanBase.h"
#include <iostream>
#include <stdexcept>
#include <functional>

VulkanBase::VulkanBase() {
    initWindow();
    initVulkan();
}

VulkanBase::~VulkanBase() {
    cleanup();
}

void VulkanBase::run() {
    mainLoop();
}

void VulkanBase::initWindow() {
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    window = glfwCreateWindow(VkUtils::WIDTH, VkUtils::HEIGHT, "Vulkan Window", nullptr, nullptr);
    glfwSetWindowUserPointer(window, this);
    glfwSetFramebufferSizeCallback(window, framebufferResizeCallback);
}

void VulkanBase::initVulkan() {
    createInstance();
    setupDebugMessenger();
    createSurface();
    pickPhysicalDevice();
    createLogicalDevice();
    createSwapChain();
    createImageViews();
    createRenderPass();
    createGraphicsPipeline();
    createFrameBuffers();
    createCommandPool();
    createCommandBuffers();
    createSyncObjects();
}

void VulkanBase::mainLoop() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        drawFrame();
    }
    vkDeviceWaitIdle(device);
}

void VulkanBase::cleanup() {
    for (size_t i = 0; i < imageAvailableSemaphores.size(); i++) {
        vkDestroySemaphore(device, renderFinishedSemaphores[i], nullptr);
        vkDestroySemaphore(device, imageAvailableSemaphores[i], nullptr);
        vkDestroyFence(device, inFlightFences[i], nullptr);
    }

    vkDestroyCommandPool(device, commandPool, nullptr);

    for (auto framebuffer : swapChainFramebuffers) {
        vkDestroyFramebuffer(device, framebuffer, nullptr);
    }

    vkDestroyPipeline(device, graphicsPipeline, nullptr);
    vkDestroyPipelineLayout(device, pipelineLayout, nullptr);
    vkDestroyRenderPass(device, renderPass, nullptr);

    for (auto imageView : swapChainImageViews) {
        vkDestroyImageView(device, imageView, nullptr);
    }

    vkDestroySwapchainKHR(device, swapChain, nullptr);
    vkDestroyDevice(device, nullptr);

    if (VkUtils::enableValidationLayers) {
        VkUtils::DestroyDebugUtilsMessengerEXT(instance, debugMessenger, nullptr);
    }

    vkDestroySurfaceKHR(instance, surface, nullptr);
    vkDestroyInstance(instance, nullptr);

    glfwDestroyWindow(window);
    glfwTerminate();
}

void VulkanBase::createInstance() {
    // Implementation of instance creation with validation layers and extensions
}

void VulkanBase::setupDebugMessenger() {
    // Implementation of debug messenger setup
}

void VulkanBase::createSurface() {
    // Implementation to create a surface
}

void VulkanBase::pickPhysicalDevice() {
    // Implementation to pick and validate suitable physical device
}

void VulkanBase::createLogicalDevice() {
    // Implementation to create a logical device and retrieve queues
}

void VulkanBase::createSwapChain() {
    // Implementation to create a swap chain
}

void VulkanBase::createImageViews() {
    // Implementation to create image views for the swap chain images
}

void VulkanBase::createRenderPass() {
    // Implementation to create a render pass
}

void VulkanBase::createGraphicsPipeline() {
    // Implementation to create graphics pipeline
}

void VulkanBase::createFrameBuffers() {
    // Implementation to create framebuffers for each swap chain image view
}

void VulkanBase::createCommandPool() {
    // Implementation to create a command pool
}

void VulkanBase::createCommandBuffers() {
    // Implementation to allocate and record command buffers
}

void VulkanBase::createSyncObjects() {
    // Implementation to create synchronization objects for frame drawing
}

void VulkanBase::drawFrame() {
    // Implementation to submit command buffer to the queue and present the image
}

void VulkanBase::framebufferResizeCallback(GLFWwindow* window, int width, int height) {
    auto app = reinterpret_cast<VulkanBase*>(glfwGetWindowUserPointer(window));
    app->framebufferResized = true;
}

