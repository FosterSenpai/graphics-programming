#version 460 core

// How the shader should interpret the input data
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

// Inputs
uniform mat4 model_matrix;

// Outputs to fragment shader
out vec3 fragment_color;
out vec3 fragment_position;

// Shader functionalty
void main()
{
	gl_Position = model_matrix * vec4(position, 1.0);
	fragment_color = color;
}