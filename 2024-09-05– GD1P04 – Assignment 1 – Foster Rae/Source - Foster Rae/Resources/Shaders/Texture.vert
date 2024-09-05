#version 460 core

// Vertex Data Interpretation
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 tex_coords;

// Inputs
uniform mat4 model_matrix;

// Outputs to Fragment Shader
out vec3 frag_color;
out vec2 frag_tex_coords;

// Shader Functionality
void main()
{
	gl_Position = model_matrix * vec4(position, 1.0); // Apply model matrix to vertex position
	frag_color = color; // Pass color to fragment shader
	frag_tex_coords = tex_coords; // Pass texture coordinates to fragment shader
}