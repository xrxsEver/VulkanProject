#pragma once

#include "vulkanbase/VulkanUtil.h"
#include "DAEDataBuffer.h"
#include "Vertex.h"
class DAEDataBuffer;
template <class UBO>
class DAEUniformBufferObject
{
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

    DAEUniformBufferObject(VkDevice device, VkDeviceSize size) {
        // Constructor implementation, if necessary
    }

    DAEDataBuffer* operator->() {
        return m_UBOBuffer.get();
    }

private:
    std::unique_ptr<DAEDataBuffer> m_UBOBuffer;
    UBO m_UBOSrc;
};
