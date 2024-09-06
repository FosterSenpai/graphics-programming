#version 460 core

// Input from vertex shader
in vec3 frag_colour;
in vec2 frag_tex_coords;

// Uniform inputs
uniform sampler2D texture_0;

// Output
out vec4 final_color;

// Shader functionality
void main()
{
	final_color = texture(texture_0, frag_tex_coords);
}