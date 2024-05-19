#pragma once

#include <vulkan/vulkan.h>
#include <vector>
#include <memory>
#include <string>
#include "DAEDescriptorPool.h"
#include <Vertex.h>

class Shader2D {
public:
    Shader2D(const std::string& vertexShaderFile, const std::string& fragmentShaderFile);

    void initialize(const VkPhysicalDevice& vkPhysicalDevice, const VkDevice& vkDevice, size_t count);
    void destroyShaderModules(const VkDevice& vkDevice);

    std::vector<VkPipelineShaderStageCreateInfo> getShaderStages() const;

private:
    std::unique_ptr<DAEDescriptorPool<VertexUBO>> m_DescriptorPool;
    std::string m_VertexShaderFile;
    std::string m_FragmentShaderFile;
    VkShaderModule m_VertexShaderModule;
    VkShaderModule m_FragmentShaderModule;

    VkShaderModule createShaderModule(const VkDevice& vkDevice, const std::vector<char>& code);
    VkPipelineShaderStageCreateInfo createShaderStageInfo(VkShaderModule shaderModule, VkShaderStageFlagBits stage) const;
};
