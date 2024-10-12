#version 460 core

// Input from vertex shader
in vec3 frag_color;
in vec2 frag_tex_coords;

// Uniform inputs
uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform float time;

// Output
out vec4 final_color;

// Shader functionality
void main()
{
    // Calculate the mix amount using a step function
    float mix_amount = mod(floor(time / 2.0), 2.0); // Changes between 0 and 1 every 2 seconds

    // Mix the two textures based on the calculated mix amount
    final_color = mix(texture(texture_0, frag_tex_coords), texture(texture_1, frag_tex_coords), 0);
}