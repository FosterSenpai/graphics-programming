#version 460 core

// Input from vertex shader
in vec3 frag_colour;
in vec2 frag_tex_coords;

// Uniform inputs
uniform sampler2D texture_0;
uniform bool is_animated; // Flag to switch between modes
uniform float offset;     // Offset for animation

// Output
out vec4 final_color;

// Shader functionality
void main()
{
    vec2 tex_coords = frag_tex_coords;

    if (is_animated) {
        // Apply offset for animation
        tex_coords.x += offset;
    }

    final_color = texture(texture_0, tex_coords);
}