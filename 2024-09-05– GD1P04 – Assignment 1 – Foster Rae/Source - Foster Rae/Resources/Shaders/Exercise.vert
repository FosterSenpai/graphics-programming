#version 460 core

// How to interpret the data in the vertex buffer.
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;
layout(location = 2) in vec2 tex_coords;

// Inputs.
uniform mat4 model_matrix;

// Outputs to the fragment shader.
out vec3 frag_color;
out vec2 frag_tex_coords;

// Main shader functionality.
void main()
{
	gl_Position = model_matrix * vec4(position, 1.0); // Apply the model matrix to the vertex position.
	frag_color = color;								  // Pass the color to the fragment shader.
	frag_tex_coords = tex_coords;					  // Pass the texture coordinates to the fragment shader.
}