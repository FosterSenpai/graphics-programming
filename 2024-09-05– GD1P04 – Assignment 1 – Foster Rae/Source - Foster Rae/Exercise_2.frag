#version 460 core

// Input from vertex shader
in vec3 frag_color;
in vec2 frag_tex_coords;

// Uniform inputs
uniform sampler2D texture_0;
uniform sampler2D texture_1;
uniform sampler2D texture_2;
uniform float time;
uniform int use_spritesheet;

// Output
out vec4 final_color;

// Shader functionality
void main()
{
    // Calculate the mix amount using a sine function
    float mix_amount = (sin(time * 2.0 * 3.14159) + 1.0) / 2.0; // Oscillates between 0 and 1 every half second

    // Check if first or second quad
    if (use_spritesheet == 1) {
        // Use texture_2 for the second quad
        final_color = texture(texture_2, frag_tex_coords);
    } else {
        // Mix the two textures based on the calculated mix amount
        final_color = mix(texture(texture_0, frag_tex_coords), texture(texture_1, frag_tex_coords), mix_amount);
    }
}