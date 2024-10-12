#version 460 core

// Input from vertex shader
in vec3 frag_color;
in vec2 frag_tex_coords;

// Uniform inputs
uniform sampler2D texture_0;
uniform sampler2D texture_1;

// Output
out vec4 final_color;

// Shader functionality
void main()
{
	final_color = mix(texture(texture_0, frag_tex_coords), texture(texture_1, frag_tex_coords), 0.5f);
}