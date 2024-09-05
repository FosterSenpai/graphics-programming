#version 460 core

in vec3 fragment_color; // Input color from vertex shader.
in float fragment_time;

out vec4 final_color; // Output color to the framebuffer after doing stuff.

void main()
{
    // Use the sine function to make the color fade in and out.
    // The sine function returns a value between -1 and 1, so we multiply by 0.5 and add 0.5 to get a value between 0 and 1. (surely this is right Callan)
    final_color = vec4(fragment_color, 1.0f) * (sin(fragment_time) * 0.5 + 0.5);
	// Clamp would give a smoother fade.
}