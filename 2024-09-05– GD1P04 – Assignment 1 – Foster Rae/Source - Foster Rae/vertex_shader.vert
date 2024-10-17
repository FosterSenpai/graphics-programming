#version 460 core

// How to interpret the data in the vertex buffer. Dont change.
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 tex_coords;

// Inputs.
uniform mat4 model_matrix;      // Model matrix
uniform mat4 view_matrix;       // View matrix
uniform mat4 projection_matrix; // Projection matrix

// Outputs to the fragment shader.
out vec2 frag_tex_coords; // Pass texture coordinates to fragment shader
out vec3 frag_normal;     // Pass normal to fragment shader
out vec3 frag_position;   // Pass position to fragment shader

// Main shader functionality.
void main() {
    frag_tex_coords = tex_coords;

    // Transform the normal and position to world space.
    frag_normal = mat3(transpose(inverse(model_matrix))) * normal;            // Transform normal to world space
    frag_position = vec3(model_matrix * vec4(position, 1.0));                 // Transform position to world space
    // Apply the model, view and projection matrices to the position.
    gl_Position = projection_matrix * view_matrix * vec4(frag_position, 1.0); // Transform position to clip space
}