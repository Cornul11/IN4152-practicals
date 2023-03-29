#version 430

// Global variables for lighting calculations
layout (location = 1) uniform vec3 Ks;
layout (location = 2) uniform vec3 cameraPos;
layout (location = 3) uniform vec3 lightPos;
layout (location = 4) uniform float specularExponent;
layout (location = 5) uniform sampler2D texToon;


// Output for on-screen color
layout (location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPos;// World-space position
in vec3 fragNormal;// World-space normal


void main()
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightPos - fragPos);
    vec3 R = reflect(-L, N);
    vec3 V = normalize(cameraPos - fragPos);
    vec3 H = normalize(L + V);

    // specularExponent * 5 because Blinn-Phong needs a higher value to achieve a similar specular effect
    outColor = texture(texToon, vec2(pow(max(dot(N, H), 0.0), specularExponent * 5), 0.0));
}