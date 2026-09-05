#version 450

layout(location = 0) in vec3 fragPos;
layout(location = 1) in vec2 fragTexCoord;
layout(location = 2) in vec3 fragNormal;
layout(location = 3) in vec3 fragColor;

layout(set = 0, binding = 0) uniform UniformBufferObject {
    mat4 view;
    mat4 proj;
    vec3 lightDirection;
    vec3 lightColor;
} ubo;

layout(binding = 1) uniform sampler2D texSampler;

layout(location = 0) out vec4 outColor;

void main() {
    float diffuse = max(dot(fragNormal, ubo.lightDirection), 0.0);
    vec4 col = texture(texSampler, fragTexCoord);
    outColor = vec4(col.xyz * diffuse, col.w);
}