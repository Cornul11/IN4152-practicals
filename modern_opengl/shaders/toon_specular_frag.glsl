#version 430

// Global variables for lighting calculations
layout (location = 1) uniform int toonIntervals;
layout (location = 2) uniform float toonThreshold;
layout (location = 3) uniform float specularExponent;
layout (location = 4) uniform vec3 Kd;
layout (location = 5) uniform vec3 Ks;
layout (location = 6) uniform vec3 lightPos;
layout (location = 7) uniform vec3 lightColor;
layout (location = 8) uniform vec3 cameraPos;

// Output for on-screen color
layout(location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPos; // World-space position
in vec3 fragNormal; // World-space normal

void main()
{
    vec3 N = normalize(fragNormal);
    vec3 L = normalize(lightPos - fragPos);

    vec3 R = reflect(-L, N);
    vec3 V = normalize(cameraPos - fragPos);
    vec3 H = normalize(L + V);

    // specularExponent * 5 because Blinn-Phong needs a higher value to achieve a similar specular effect
    float specular = pow(max(dot(N, H), 0.0), specularExponent * 5);
    vec3 finalColor = vec3(1) * round(specular);// full white or black
    // Output the normal as color
    outColor = vec4(Ks * finalColor * lightColor, 1.0);
}