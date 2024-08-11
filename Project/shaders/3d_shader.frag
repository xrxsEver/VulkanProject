#version 450

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) in vec3 fragNormal;
layout(location = 1) in vec3 fragPosition;
layout(location = 2) in vec3 fragColor;
layout(location = 3) in vec2 fragTexCoord;

layout(location = 0) out vec4 outColor;

// Declare uniforms inside a uniform block
layout(binding = 2) uniform LightInfo {
    vec3 lightPos;
    vec3 viewPos;
} lightInfo;

void main() {
    // Ambient lighting
    float ambientStrength = 0.8;
    vec3 ambient = ambientStrength * vec3(1.0, 1.0, 1.0);
    
    // Diffuse lighting
    vec3 norm = normalize(fragNormal);
    vec3 lightDir = normalize(lightInfo.lightPos - fragPosition);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * vec3(1.0, 1.0, 1.0);
    
    // Specular lighting
    float specularStrength = 0.5;
    vec3 viewDir = normalize(lightInfo.viewPos - fragPosition);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * vec3(1.0, 1.0, 1.0);
    
    vec3 result = (ambient + diffuse + specular) * fragColor;
    outColor = vec4(result * texture(texSampler, fragTexCoord).rgb, 1.0);
}
