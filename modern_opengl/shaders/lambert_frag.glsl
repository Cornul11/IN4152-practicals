#version 430

// Global variables for lighting calculations
layout (location = 1) uniform vec3 Kd;
layout (location = 2) uniform vec3 lightPos;
layout (location = 3) uniform vec3 lightColor;

// Output for on-screen color
layout(location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPos; // World-space position
in vec3 fragNormal; // World-space normal

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightPos - fragPos);

    outColor = vec4(Kd * dot(N, L) * lightColor, 1.0);
}