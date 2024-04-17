#include <glm/glm.hpp>

struct Vertex
{
	glm::vec2 position;
	glm::vec3 color;
};


struct VertexUBO {
	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 proj;
};

struct MeshData {
	glm::mat4 model;
};

struct ViewProjection {
	glm::mat4 proj;
	glm::mat4 view;
};
