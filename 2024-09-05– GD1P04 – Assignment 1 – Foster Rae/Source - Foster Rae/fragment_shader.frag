#version 460 core

// Input from vertex shader
in vec3 frag_color; // Dont Change.
in vec2 frag_tex_coords; // Dont Change.

// Uniform inputs
// Receive textures here and set final_color to the texture you want to display.
uniform sampler2D textures[16]; // Dont Change. Max textures a shape can have is 16.
uniform int texture_count;      // Dont Change. Use this to for end of iteration loop.
uniform bool is_animated;       // Dont Change. Use this to check if the texture is animated.
uniform float time;             // Dont Change. Use this to animate the texture.

// Output
out vec4 final_color; // Dont Change.

// Shader functionality
void main()
{
    vec4 color;

    if (is_animated) {
        // Calculate the frame index based on time
        int frame_index = int(time * 8) % texture_count; // Adjust the multiplier to control animation speed

        // Debugging: Ensure frame_index is within bounds
        if (frame_index < 0 || frame_index >= texture_count) {
            color = vec4(1.0, 0.0, 0.0, 1.0); // Red color for debugging
        } else {
            color = texture(textures[frame_index], frag_tex_coords);
        }
    } else {
        // Use the first texture as the base for static shapes
        color = texture(textures[0], frag_tex_coords);
    }

    final_color = color;
}