#version 330 core

// Interpolated values from the vertex shaders
in vec3 fragColor;
in vec2 UV;

// output data
out vec3 color;

uniform sampler2D myTextureSampler;
uniform float distance; 
void main()
{
    // Output color = color specified in the vertex shader,
    // interpolated between all 3 surrounding vertices of the triangle
    if(UV.x >= 0)
        color = distance * texture( myTextureSampler, UV ).rgb;
    else
        color = distance * fragColor;
}
