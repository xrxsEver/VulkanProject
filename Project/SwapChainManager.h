#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include "vulkanbase/VulkanBase.h"
#include "vulkanbase/VulkanUtil.h"

struct SwapChainSupportDetails {
    VkSurfaceCapabilitiesKHR capabilities;    // Capabilities of the surface
    std::vector<VkSurfaceFormatKHR> formats;  // Formats supported by the surface
    std::vector<VkPresentModeKHR> presentModes;  // Presentation modes supported by the surface
};


class SwapChainManager {
public:
    SwapChainManager(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, GLFWwindow* window);
    ~SwapChainManager();

    void createSwapChain();
    void createImageViews();
    void cleanupSwapChain();

    VkSwapchainKHR getSwapChain() const;
    std::vector<VkImage> getSwapChainImages() const;
    std::vector<VkImageView> getSwapChainImageViews() const;
    VkFormat getSwapChainImageFormat() const;
    VkExtent2D getSwapChainExtent() const;

private:
    VkDevice m_device;
    VkPhysicalDevice m_physicalDevice;
    VkSurfaceKHR m_surface;
    GLFWwindow* m_window; 

    VkSwapchainKHR m_swapChain;
    std::vector<VkImage> m_swapChainImages;
    std::vector<VkImageView> m_swapChainImageViews;
    VkFormat m_swapChainImageFormat;
    VkExtent2D m_swapChainExtent;

    SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
    VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
    VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
    VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
};
