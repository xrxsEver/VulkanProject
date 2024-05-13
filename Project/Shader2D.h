#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <array>
#include <iostream>
#include "DAEDataBuffer.h"
#include "DAEDescriptorPool.h"
#include "Vertex.h"

class Shader2D
{

public:
	Shader2D(
		const std::string& vertexShaderFile,
		const std::string& fragmentShaderFile);
	~Shader2D() = default;

	void initialize(const VkPhysicalDevice& vkPhysicalDevice, const VkDevice& vkDevice);
	void destroyShaderModules(const VkDevice& vkDevice);

	std::vector<VkPipelineShaderStageCreateInfo>&
		getShaderStages() {
		return m_ShaderStage;
	}

	VkPipelineVertexInputStateCreateInfo createVertexInputStateInfo();
	VkPipelineInputAssemblyStateCreateInfo createInputAssemblyStateInfo();

	void createDescriptorSetLayout(const VkDevice& vkDevice);
	const VkDescriptorSetLayout& getDescriptorSetLayout()
	{
		return m_DescriptorSetLayout;
	}
	void bindDescriptorSet(VkCommandBuffer commandBuffer, VkPipelineLayout pipelineLayout, size_t index);

private:
	VkDescriptorSetLayout m_DescriptorSetLayout;
	std::unique_ptr<DAEDataBuffer> m_UBOBuffer;

	std::unique_ptr<DAEDescriptorPool<VertexUBO>> m_DescriptorPool;

	VkPipelineShaderStageCreateInfo createFragmentShaderInfo(const VkDevice& vkDevice);
	VkPipelineShaderStageCreateInfo createVertexShaderInfo(const VkDevice& vkDevice);

	VkShaderModule createShaderModule(const VkDevice& device, const std::vector<char>& code);

	std::string m_VertexShaderFile;
	std::string m_FragmentShaderFile;

	std::vector<VkPipelineShaderStageCreateInfo> m_ShaderStage;

	Shader2D(const Shader2D&) = delete;
	Shader2D& operator=(const Shader2D&) = delete;

	Shader2D(const Shader2D&&) = delete;
	Shader2D& operator=(const Shader2D&&) = delete;
};


static VkVertexInputBindingDescription getBindingDescription() {
	VkVertexInputBindingDescription bindingDescription{};
	bindingDescription.binding = 0;
	bindingDescription.stride = sizeof(Vertex);
	bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

	return bindingDescription;
}

static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions()
{
	std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

	attributeDescriptions[0].binding = 0;
	attributeDescriptions[0].location = 0;
	attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;  // For position
	attributeDescriptions[0].offset = offsetof(Vertex, pos);

	attributeDescriptions[1].binding = 0;
	attributeDescriptions[1].location = 1; // Ensure this is different
	attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;  // For color
	attributeDescriptions[1].offset = offsetof(Vertex, color);

	//auto attributeDescriptions = Vertex::getAttributeDescriptions();
	for (const auto& desc : attributeDescriptions) {
		std::cout << "Binding: " << desc.binding << ", Location: " << desc.location
			<< ", Format: " << desc.format << ", Offset: " << desc.offset << std::endl;
	}

	return attributeDescriptions;
}

const std::vector<Vertex> vertices = {
{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

