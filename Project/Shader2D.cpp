#include "Shader2D.h"
#include "vulkanbase/VulkanUtil.h"
#include <fstream>

Shader2D::Shader2D(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    : m_VertexShaderFile(vertexShaderFile), m_FragmentShaderFile(fragmentShaderFile) {}

void Shader2D::initialize(const VkDevice& vkDevice, size_t count) {
    m_DescriptorPool = std::make_unique<DAEDescriptorPool<VertexUBO>>(vkDevice, count);

    m_VertexShaderModule = createShaderModule(vkDevice, VkUtils::readFile(m_VertexShaderFile));
    m_FragmentShaderModule = createShaderModule(vkDevice, VkUtils::readFile(m_FragmentShaderFile));
}

void Shader2D::destroyShaderModules(const VkDevice& vkDevice) {
    vkDestroyShaderModule(vkDevice, m_VertexShaderModule, nullptr);
    vkDestroyShaderModule(vkDevice, m_FragmentShaderModule, nullptr);
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
