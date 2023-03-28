#version 430

// Global variables for lighting calculations
layout (location = 1) uniform vec3 Kd;

// Output for on-screen color
layout(location = 0) out vec4 outColor;

// Interpolated output data from vertex shader
in vec3 fragPos; // World-space position
in vec3 fragNormal; // World-space normal

void main()
{
    outColor = vec4(Kd * normalize(fragPos) * normalize(fragNormal), 1.0);
    // Output the normal as color
}