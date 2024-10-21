#version 460 core
// Output.
out vec4 FragColor;

// Input from vertex shader.
in vec2 TexCoord;

// Inputs from application.
uniform sampler2D texture_diffuse1;
uniform sampler2D texture_diffuse2;
uniform sampler2D texture_diffuse3;
uniform sampler2D texture_specular1;
uniform sampler2D texture_specular2;
uniform sampler2D texture_specular3;
uniform int active_texture; // Uniform to select which texture to use.
uniform float time; // This isnt being used right now. Remember to use or remove.

void main()
{
    vec4 color;
    if (active_texture == 0) {
        color = texture(texture_diffuse1, TexCoord);
    } else if (active_texture == 1) {
        color = texture(texture_diffuse2, TexCoord);
    } else if (active_texture == 2) {
        color = texture(texture_diffuse3, TexCoord);
    } else if (active_texture == 3) {
        color = texture(texture_specular1, TexCoord);
    } else if (active_texture == 4) {
        color = texture(texture_specular2, TexCoord);
    } else if (active_texture == 5) {
        color = texture(texture_specular3, TexCoord);
    } else {
        color = vec4(1.0, 0.0, 1.0, 1.0); // Default to magenta if no valid texture is selected
    }

	// Output the color.
	FragColor = color;
}