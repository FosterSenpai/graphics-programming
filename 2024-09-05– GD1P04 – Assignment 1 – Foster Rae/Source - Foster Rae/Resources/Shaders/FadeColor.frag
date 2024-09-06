#version 460 core

in vec3 fragment_color; // Input color from vertex shader.
in float fragment_time;

uniform vec3 blend_color;

out vec4 final_color; // Output color to the framebuffer after doing stuff.

void main()
{
    // Use the sine function to make the color fade in and out.
    float fade_factor = sin(fragment_time) * 0.5 + 0.5;
    vec3 mixed_color = mix(fragment_color, blend_color, fade_factor); // Blend the colors
    final_color = vec4(mixed_color, 1.0f);
}