
#pragma once

#include "vulkanbase/VulkanUtil.h"
#include "DAEDataBuffer.h"

template <class UBO>
class DAEUniformBufferObject
{
public:
	void initialize(const VulkanContext& context);
	void upload();
	void setData(UBO ubo) {
		m_UBOSrc = ubo;
	}

	VkBuffer getVkBuffer() {
		return m_UBOBuffer->getVkBuffer();
	}
private:
	std::unique_ptr<DAEDataBuffer> m_UBOBuffer;
	UBO m_UBOSrc;
};
