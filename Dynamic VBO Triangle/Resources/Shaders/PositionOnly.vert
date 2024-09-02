#version 460 core

// How the shader should interpret the input data
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

// Inputs
uniform mat4 translation_matrix;
uniform mat4 rotation_matrix;

// Outputs to fragment shader
out vec3 fragment_color;
out vec3 fragment_position;

// Shader functionalty
void main()
{
	gl_Position = translation_matrix * rotation_matrix *vec4(position, 1.0);
	fragment_color = color;
}