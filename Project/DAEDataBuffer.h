#pragma once 

#include "vulkanbase/VulkanBase.h"

#include <stdexcept>
class DAEDataBuffer
{
public:
	DAEDataBuffer(
		VkPhysicalDevice physicalDevice,
		VkDevice device,
		VkBufferUsageFlags usage,
		VkMemoryPropertyFlags properties,
		VkDeviceSize size
	);

	~DAEDataBuffer() {
		destroy();
	}

	void upload(VkDeviceSize size, void* data);
	void map(VkDeviceSize size, void* data);
	void destroy();
	void bindAsVertexBuffer(VkCommandBuffer commandBuffer);
	void bindAsIndexBuffer(VkCommandBuffer commandBuffer);
	VkBuffer getVkBuffer();
	VkDeviceSize getSizeInBytes();
private:
	uint32_t findMemoryType(VkPhysicalDevice physicalDevice, uint32_t typeFilter, VkMemoryPropertyFlags properties);

	VkDevice m_VkDevice;
	VkDeviceSize m_Size;
	VkBuffer m_VkBuffer;
	VkDeviceMemory m_VkBufferMemory;
};
