#version 460 core

in vec3 fragment_color; // Input color from vertex shader.

uniform float current_time;

out vec4 final_color; // Output color to the framebuffer after doing stuff.

void main()
{
    // Use the sine function to make the color fade in and out.
	final_color = vec4(fragment_color, 1.0f) * abs(sin(current_time));
	// Clamp would give a smoother fade.
}