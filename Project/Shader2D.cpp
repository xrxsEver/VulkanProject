#include "Shader2D.h"
#include "vulkanbase/VulkanUtil.h"
#include <fstream>
#include <stdexcept>

Shader2D::Shader2D(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    : m_VertexShaderFile(vertexShaderFile), m_FragmentShaderFile(fragmentShaderFile),
    m_VertexShaderModule(VK_NULL_HANDLE), m_FragmentShaderModule(VK_NULL_HANDLE) {}

void Shader2D::initialize(const VkPhysicalDevice& vkPhysicalDevice, const VkDevice& vkDevice, size_t count) {
    m_DescriptorPool = std::make_unique<DAEDescriptorPool<VertexUBO>>(vkDevice, count);

    // Ensure the shader files are correctly read
    auto vertexCode = VkUtils::readFile(m_VertexShaderFile);
    if (vertexCode.empty()) {
        throw std::runtime_error("Failed to load vertex shader file!");
    }
    m_VertexShaderModule = createShaderModule(vkDevice, vertexCode);

    auto fragmentCode = VkUtils::readFile(m_FragmentShaderFile);
    if (fragmentCode.empty()) {
        throw std::runtime_error("Failed to load fragment shader file!");
    }
    m_FragmentShaderModule = createShaderModule(vkDevice, fragmentCode);
}

void Shader2D::destroyShaderModules(const VkDevice& vkDevice) {
    if (m_VertexShaderModule != VK_NULL_HANDLE) {
        vkDestroyShaderModule(vkDevice, m_VertexShaderModule, nullptr);
    }
    if (m_FragmentShaderModule != VK_NULL_HANDLE) {
        vkDestroyShaderModule(vkDevice, m_FragmentShaderModule, nullptr);
    }
}

VkShaderModule Shader2D::createShaderModule(const VkDevice& vkDevice, const std::vector<char>& code) {
    VkShaderModuleCreateInfo createInfo{};
    createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
    createInfo.codeSize = code.size();
    createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

    VkShaderModule shaderModule;
    if (vkCreateShaderModule(vkDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS) {
        throw std::runtime_error("failed to create shader module!");
    }

    return shaderModule;
}

VkPipelineShaderStageCreateInfo Shader2D::createShaderStageInfo(VkShaderModule shaderModule, VkShaderStageFlagBits stage) const {
    VkPipelineShaderStageCreateInfo shaderStageInfo{};
    shaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    shaderStageInfo.stage = stage;
    shaderStageInfo.module = shaderModule;
    shaderStageInfo.pName = "main";

    return shaderStageInfo;
}

std::vector<VkPipelineShaderStageCreateInfo> Shader2D::getShaderStages() const {
    return {
        createShaderStageInfo(m_VertexShaderModule, VK_SHADER_STAGE_VERTEX_BIT),
        createShaderStageInfo(m_FragmentShaderModule, VK_SHADER_STAGE_FRAGMENT_BIT)
    };
}
