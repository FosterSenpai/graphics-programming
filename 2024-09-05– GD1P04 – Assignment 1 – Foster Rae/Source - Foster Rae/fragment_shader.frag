#version 460 core

// Input from vertex shader
in vec2 frag_tex_coords; // Texture coordinates from vertex shader
in vec3 frag_normal;     // Normal from vertex shader
in vec3 frag_position;   // Position from vertex shader

// Uniform inputs
// Objects can have 3 Diffuse textures and 3 Specular textures.
uniform sampler2D texture_diffuse_1;
uniform sampler2D texture_diffuse_2;
uniform sampler2D texture_diffuse_3;
uniform sampler2D texture_specular_1;
uniform sampler2D texture_specular_2;
uniform sampler2D texture_specular_3;
uniform vec3 view_position;  // Camera position

// Output
out vec4 final_color; // Dont Change.

// Shader functionality
void main()
{
    // Sample the diffuse textures
    vec4 diffuse1 = texture(texture_diffuse_1, frag_tex_coords);
    vec4 diffuse2 = texture(texture_diffuse_2, frag_tex_coords);
    vec4 diffuse3 = texture(texture_diffuse_3, frag_tex_coords);

    // Sample the specular textures
    vec4 specular1 = texture(texture_specular_1, frag_tex_coords);
    vec4 specular2 = texture(texture_specular_2, frag_tex_coords);
    vec4 specular3 = texture(texture_specular_3, frag_tex_coords);

    // Blend the textures together
    vec4 diffuse_color = (diffuse1 + diffuse2 + diffuse3) / 3.0;
    vec4 specular_color = (specular1 + specular2 + specular3) / 3.0;

    // Combine diffuse and specular colors
    vec4 color = diffuse_color + specular_color;

    // Set the final color
    final_color = color;
}