#pragma once

#include "vulkanbase/VulkanUtil.h"
#include "DAEDataBuffer.h"
#include "Vertex.h"
class DAEDataBuffer;

template <class UBO>
class DAEUniformBufferObject {
public:
    void initialize(const VulkanContext& context);
    void upload();
    void setData(UBO ubo) {
        m_UBOSrc = ubo;
    }
    void update(UBO data) {
        setData(data);
        upload();
    }

    VkBuffer getVkBuffer() {
        return m_UBOBuffer->getVkBuffer();
    }

    DAEUniformBufferObject(VkPhysicalDevice physicalDevice, VkDevice device, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkDeviceSize size)
        : m_UBOBuffer(std::make_unique<DAEDataBuffer>(physicalDevice, device, usage, properties, size)) {}

    DAEDataBuffer* operator->() {
        return m_UBOBuffer.get();
    }

private:
    std::unique_ptr<DAEDataBuffer> m_UBOBuffer;
    UBO m_UBOSrc;
};


template <class UBO>
void DAEUniformBufferObject<UBO>::initialize(const VulkanContext& context) {
    VkDeviceSize bufferSize = sizeof(UBO);
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