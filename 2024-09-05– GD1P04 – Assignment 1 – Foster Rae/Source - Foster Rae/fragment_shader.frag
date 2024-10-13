#version 460 core

// Input from vertex shader
in vec3 frag_color; // Dont Change.
in vec2 frag_tex_coords; // Dont Change.

// Uniform inputs
// Receive textures here and set final_color to the texture you want to display.
uniform sampler2D textures[16]; // Dont Change. Max textures a shape can have is 16.
uniform int texture_count; // Dont Change. Use this to for end of iteration loop.

// Output
out vec4 final_color; // Dont Change.

// Shader functionality
void main()
{
    vec4 color = texture(textures[0], frag_tex_coords); // Start with the first texture as the base

    // Loop through remaining textures and blend them on top
    for (int i = 1; i < texture_count; ++i) {
        vec4 tex_color = texture(textures[i], frag_tex_coords);
        // Alpha blending: new_color = old_color * (1 - tex_color.a) + tex_color * tex_color.a
        color = mix(color, tex_color, tex_color.a);
    }

    final_color = color;
}