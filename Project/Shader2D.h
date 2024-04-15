#pragma once
#include <vulkan/vulkan_core.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <array>
 
class Shader2D
{

public:
	Shader2D(
		const std::string& vertexShaderFile,
		const std::string& fragmentShaderFile
	) : m_VertexShaderFile{ vertexShaderFile },
		m_FragmentShaderFile{ fragmentShaderFile }
	{

	}

	~Shader2D() = default;

	void initialize(const VkDevice& vkDevice);
	void destroyShaderModules(const VkDevice& vkDevice);

	std::vector<VkPipelineShaderStageCreateInfo>&
		getShaderStages() {
		return m_ShaderStage;
	}

	VkPipelineVertexInputStateCreateInfo createVertexInputStateInfo();
	VkPipelineInputAssemblyStateCreateInfo createInputAssemblyStateInfo();

private:

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


struct Vertex {
	glm::vec2 pos;
	glm::vec3 color;

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
		attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
		attributeDescriptions[0].offset = offsetof(Vertex, pos);

		attributeDescriptions[1].binding = 0;
		attributeDescriptions[1].location = 1;
		attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
		attributeDescriptions[1].offset = offsetof(Vertex, color);

		return attributeDescriptions;
	}


};

const std::vector<Vertex> vertices = {
{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}}
};

