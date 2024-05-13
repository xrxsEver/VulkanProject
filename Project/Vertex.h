#pragma once

#include <glm/glm.hpp>
#include <vulkan/vulkan.h>
#include <array>

struct Vertex {
    glm::vec2 pos;   // Position vector
    glm::vec3 color; // Color vector

    // Static method to get the binding description for vertex inputs
    static VkVertexInputBindingDescription getBindingDescription() {
        VkVertexInputBindingDescription bindingDescription{};
        bindingDescription.binding = 0; // Index of the binding in the array of bindings
        bindingDescription.stride = sizeof(Vertex); // Distance between elements within the buffer
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX; // Move to the next data entry after each vertex

        return bindingDescription;
    }

    // Static method to get attribute descriptions for vertex inputs
    static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
        std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

        // Position attribute
        attributeDescriptions[0].binding = 0; // Which binding the data is taken from
        attributeDescriptions[0].location = 0; // Location in the shader where data will be read
        attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT; // Format the shader will read
        attributeDescriptions[0].offset = offsetof(Vertex, pos); // Offset within the structure

        // Color attribute
        attributeDescriptions[1].binding = 0; // Which binding the data is taken from
        attributeDescriptions[1].location = 1; // Location in the shader where data will be read
        attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT; // Format the shader will read
        attributeDescriptions[1].offset = offsetof(Vertex, color); // Offset within the structure

        return attributeDescriptions;
    }
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
