#include "DAEMesh.h"


void DAEMesh::draw(VkPipelineLayout pipelineLayout, VkCommandBuffer
	commandBuffer)
{
	m_VertexBuffer->bindAsVertexBuffer(commandBuffer);
	m_IndexBuffer->bindAsIndexBuffer(commandBuffer);
	vkCmdDrawIndexed(commandBuffer,
		static_cast<uint32_t>(m_Indices.size()), 1, 0, 0, 0);
}