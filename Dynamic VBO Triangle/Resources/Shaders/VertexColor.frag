#version 460 core

in vec3 frag_color; // Input color from vertex shader.

out vec4 final_color; // Output color to the framebuffer after doing stuff.

void main()
{
	final_color = vec4(frag_color, 1.0f);
}