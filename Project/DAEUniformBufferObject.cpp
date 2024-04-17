#include "DAEUniformBufferObject.h"

template <class UBO>
void DAEUniformBufferObject<UBO>::initialize(const VulkanContext& context) {
    // Calculate the size of UBO
    VkDeviceSize bufferSize = sizeof(UBO);

    // Creating buffer and allocating memory
    m_UBOBuffer = std::make_unique<DAEDataBuffer>(
        context.physicalDevice,
        context.device,
        VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT,
        VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT,
        bufferSize
    );

    void* data;
    vkMapMemory(context.device, m_UBOBuffer->getMemory(), 0, bufferSize, 0, &data);
    memcpy(data, &m_UBOSrc, sizeof(UBO));
    vkUnmapMemory(context.device, m_UBOBuffer->getMemory());
}

template <class UBO>
void DAEUniformBufferObject<UBO>::upload() {
    void* data;
    VkDeviceSize bufferSize = sizeof(UBO);
    vkMapMemory(m_UBOBuffer->getDevice(), m_UBOBuffer->getMemory(), 0, bufferSize, 0, &data);
    memcpy(data, &m_UBOSrc, sizeof(UBO));
    vkUnmapMemory(m_UBOBuffer->getDevice(), m_UBOBuffer->getMemory());
}

// Explicit template instantiation
template class DAEUniformBufferObject<VertexUBO>;  

