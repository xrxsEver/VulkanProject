#pragma once  

#include <vector>
#include <memory>
#include "DAEDataBuffer.h"

template <class UBO>
class DAEDescriptorPool
{
public:
	DAEDescriptorPool(VkDevice device, size_t count);
	~DAEDescriptorPool();

	void initialize(const VkUtils::VulkanContext& context);

	void setUBO(UBO data, size_t index);
	std::vector<DAEUniformBufferObjectPtr<UBO>> m_UBOs; 


	const VkDescriptorSetLayout& getDescriptorSetLayout()
	{
		return m_DescriptorSetLayout;
	}

	void createDescriptorSets(VkDescriptorSetLayout descriptorSetLayout,
		std::initializer_list<VkBuffer> buffers);

	void bindDescriptorSet(VkCommandBuffer buffer, VkPipelineLayout layout, size_t index);
private:
	VkDevice m_Device;
	VkDeviceSize m_Size;
	VkDescriptorSetLayout m_DescriptorSetLayout;

	void createDescriptorSetLayout(const VkUtils::VulkanContext& context);
	void createUBOs(const VkUtils::VulkanContext& context);

	VkDescriptorPool m_DescriptorPool;
	std::vector<VkDescriptorSet> m_DescriptorSets;

	size_t m_Count;
};