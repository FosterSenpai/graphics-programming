#version 460 core

// Because theres only positional data, we only define the one layout
// This is the position of the vertex, its a vec3 because its 3D which is passed to the next stage
layout (location = 0) in vec3 Position;

void main()
{
	// Passing the position from the vertex shader to the next stage
	gl_Position = vec4(Position, 1.0);
}