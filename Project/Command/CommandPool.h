#pragma once

#include <vulkan/vulkan.h>

class CommandPool {
public:
    CommandPool(VkDevice device, VkPhysicalDevice physicalDevice, VkSurfaceKHR surface);
    ~CommandPool();

    void create();
    VkCommandPool getCommandPool() const;

private:
    VkDevice device;
    VkPhysicalDevice physicalDevice;
    VkSurfaceKHR surface;
    VkCommandPool commandPool;
};
