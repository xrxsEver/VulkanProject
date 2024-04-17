#include "DAEDescriptorPool.h"
#include <stdexcept>

template <class UBO>
DAEDescriptorPool<UBO>::DAEDescriptorPool(VkDevice device, size_t count)
    : m_Device(device), m_Count(count)
{
    // Constructor logic if needed
}

template <class UBO>
DAEDescriptorPool<UBO>::~DAEDescriptorPool() {
    // Cleanup
    vkDestroyDescriptorSetLayout(m_Device, m_DescriptorSetLayout, nullptr);
    vkDestroyDescriptorPool(m_Device, m_DescriptorPool, nullptr);
    // Consider destroying UBOs if not managed externally
}

template <class UBO>
void DAEDescriptorPool<UBO>::initialize(const VkUtils::VulkanContext& context) {
    createDescriptorSetLayout(context);
    createUBOs(context);
}

template <class UBO>
void DAEDescriptorPool<UBO>::setUBO(UBO data, size_t index) {
    if (index >= m_UBOs.size()) {
        throw std::out_of_range("Index out of range");
    }
    // Assuming DAEDataBuffer has a method to update data
    m_UBOs[index]->update(data);
}

template <class UBO>
void DAEDescriptorPool<UBO>::createDescriptorSets(VkDescriptorSetLayout descriptorSetLayout, std::initializer_list<VkBuffer> buffers) {
    std::vector<VkDescriptorSetLayout> layouts(m_Count, descriptorSetLayout);
    VkDescriptorSetAllocateInfo allocInfo{};
    allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.descriptorPool = m_DescriptorPool;
    allocInfo.descriptorSetCount = static_cast<uint32_t>(m_Count);
    allocInfo.pSetLayouts = layouts.data();

    m_DescriptorSets.resize(m_Count);
    if (vkAllocateDescriptorSets(m_Device, &allocInfo, m_DescriptorSets.data()) != VK_SUCCESS) {
        throw std::runtime_error("Failed to allocate descriptor sets");
    }

    for (size_t i = 0; i < m_Count; i++) {
        VkDescriptorBufferInfo bufferInfo{};
        bufferInfo.buffer = buffers.begin()[i]; // This is very naive; ensure buffer list matches count
        bufferInfo.offset = 0;
        bufferInfo.range = sizeof(UBO);

        VkWriteDescriptorSet descriptorWrite{};
        descriptorWrite.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
        descriptorWrite.dstSet = m_DescriptorSets[i];
        descriptorWrite.dstBinding = 0;
        descriptorWrite.dstArrayElement = 0;
        descriptorWrite.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
        descriptorWrite.descriptorCount = 1;
        descriptorWrite.pBufferInfo = &bufferInfo;

        vkUpdateDescriptorSets(m_Device, 1, &descriptorWrite, 0, nullptr);
    }
}

template <class UBO>
void DAEDescriptorPool<UBO>::bindDescriptorSet(VkCommandBuffer buffer, VkPipelineLayout layout, size_t index) {
    if (index >= m_DescriptorSets.size()) {
        throw std::out_of_range("Index out of range");
    }
    vkCmdBindDescriptorSets(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, layout, 0, 1, &m_DescriptorSets[index], 0, nullptr);
}

template <class UBO>
void DAEDescriptorPool<UBO>::createDescriptorSetLayout(const VkUtils::VulkanContext& context) {
    VkDescriptorSetLayoutBinding uboLayoutBinding{};
    uboLayoutBinding.binding = 0;
    uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    uboLayoutBinding.descriptorCount = 1;
    uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT; // Adjust based on actual usage
    uboLayoutBinding.pImmutableSamplers = nullptr;

    VkDescriptorSetLayoutCreateInfo layoutInfo{};
    layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    layoutInfo.bindingCount = 1;
    layoutInfo.pBindings = &uboLayoutBinding;

    if (vkCreateDescriptorSetLayout(m_Device, &layoutInfo, nullptr, &m_DescriptorSetLayout) != VK_SUCCESS) {
        throw std::runtime_error("Failed to create descriptor set layout");
    }
}

template<class UBO>
void DAEDescriptorPool<UBO>::createUBOs(const VkUtils::VulkanContext& context)
{
    m_UBOs.resize(m_Count);
    for (size_t i = 0; i < m_Count; i

}
