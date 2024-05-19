#include "DAEMesh.h"
#include <stdexcept>

// Constructor
DAEMesh::DAEMesh() {

}

// Initialize mesh resources
void DAEMesh::initialize(VkPhysicalDevice physicalDevice, VkDevice device) {
    m_VertexBuffer = std::make_unique<DAEDataBuffer>(device, physicalDevice, sizeof(Vertex) * m_Vertices.size(), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
    m_IndexBuffer = std::make_unique<DAEDataBuffer>(device, physicalDevice, sizeof(uint16_t) * m_Indices.size(), VK_BUFFER_USAGE_INDEX_BUFFER_BIT);

    // Transfer vertex data to GPU
    m_VertexBuffer->upload(sizeof(Vertex) * m_Vertices.size(), m_Vertices.data());
    // Transfer index data to GPU
    m_IndexBuffer->upload(sizeof(uint16_t) * m_Indices.size(), m_Indices.data());
}

// Destroy mesh resources
void DAEMesh::destroyMesh(VkDevice device) {
    if (m_VertexBuffer) {
        m_VertexBuffer->destroy();
    }
    if (m_IndexBuffer) {
        m_IndexBuffer->destroy();
    }
}

// Add a vertex to the mesh
void DAEMesh::addVertex(glm::vec2 pos, glm::vec3 color) {
    Vertex vertex;
    vertex.pos = pos;
    vertex.color = color;
    m_Vertices.push_back(vertex);
}

// Add a triangle to the mesh
void DAEMesh::addTriangle(uint16_t i1, uint16_t i2, uint16_t i3, uint16_t offset) {
    m_Indices.push_back(i1 + offset);
    m_Indices.push_back(i2 + offset);
    m_Indices.push_back(i3 + offset);
}


void DAEMesh::draw(VkPipelineLayout pipelineLayout, VkCommandBuffer
	commandBuffer)
{

	m_VertexBuffer->bindAsVertexBuffer(commandBuffer);
	m_IndexBuffer->bindAsIndexBuffer(commandBuffer);
	vkCmdDrawIndexed(commandBuffer,
		static_cast<uint32_t>(m_Indices.size()), 1, 0, 0, 0);
}