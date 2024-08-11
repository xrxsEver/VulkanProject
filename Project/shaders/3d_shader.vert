#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 model;
    mat4 view;
    mat4 proj;
} ubo;

layout(location = 0) in vec3 inPosition;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec2 inTexCoord;
layout(location = 3) in vec3 inNormal;

layout(location = 0) out vec3 fragNormal;
layout(location = 1) out vec3 fragPosition;
layout(location = 2) out vec3 fragColor;
layout(location = 3) out vec2 fragTexCoord;

void main() {
    // Rotate the normal vector with the model matrix
    fragNormal = mat3(ubo.model) * inNormal;
    
    // Calculate the position in world space
    fragPosition = vec3(ubo.model * vec4(inPosition, 1.0));

    fragColor = inColor;
    fragTexCoord = inTexCoord;
    
    gl_Position = ubo.proj * ubo.view * vec4(fragPosition, 1.0);
}
