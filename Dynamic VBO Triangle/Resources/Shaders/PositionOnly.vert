#version 460 core

layout (location = 0) in vec3 position; // The position of the vertex
layout (location = 1) in vec3 color; // The color of the vertex

// Color isnt used in this shader, so we can just pass it through to the next stage.
out vec3 frag_color; // Output color to the fragment shader

void main()
{
	// Passing the position from the vertex shader to the next stage
	gl_Position = vec4(position, 1.0);
	frag_color = color; // Pass the color to the fragment shader without doing anything to it.
}