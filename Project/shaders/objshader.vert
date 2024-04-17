#version 450

layout(binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
} ubo;

layout(push_constant) uniform constants
{
    mat4 model;
} push;

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inNorm;
layout(location = 2) in vec3 inColor;

layout(location = 0) out vec3 outPos;
layout(location = 1) out vec3 outColor;
layout(location = 2) out vec3 outNorm;

void main()
{
    gl_Position = ubo.proj * ubo.view * push.model * vec4(inPos, 1.0);

    outPos = vec3(push.model * vec4(inPos, 1.0));
    outColor = inColor;
    outNorm = mat3(transpose(inverse(push.model))) * inNorm;
}
