#version 430

// Global variables for lighting calculations
layout (location = 1) uniform vec3 Ks;
layout (location = 2) uniform vec3 cameraPos;
layout (location = 3) uniform vec3 lightPos;
layout (location = 4) uniform float specularExponent;

// Output for on-screen color
layout(location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPos;// World-space position
in vec3 fragNormal;// World-space normal

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightPos - fragPos);
    vec3 R = reflect(-L, N);
    vec3 V = normalize(cameraPos - fragPos);
    // Output the normal as color
    outColor = vec4(Ks * pow(max(dot(R, V), 0.0), specularExponent), 1.0);
}