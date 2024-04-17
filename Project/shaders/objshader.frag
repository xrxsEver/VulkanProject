#version 450

layout(location = 0) in vec3 inPos;
layout(location = 1) in vec3 inColor;
layout(location = 2) in vec3 inNorm;

layout(location = 0) out vec4 outColor;

const vec3 lightPos = vec3(1.2f, 1.f, 2.f);
const vec3 lightColor = vec3(.8f, .8f, 1.f);

void main()
{
    if (length(inNorm) == 0.f)
    {
        outColor = vec4(inColor, 1.0);
        return;
    }

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(inNorm);
    vec3 lightDir = normalize(lightPos - inPos);

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * inColor;

    outColor = vec4(result, 1.0);
}
