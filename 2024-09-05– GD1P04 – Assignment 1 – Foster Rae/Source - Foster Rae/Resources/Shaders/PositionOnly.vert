#version 460 core

// How the shader should interpret the input data
layout (location = 0) in vec3 position;
layout (location = 1) in vec3 color;

// Inputs
uniform mat4 model_matrix;
uniform float current_time;

// Outputs to fragment shader
out vec3 fragment_color;
out float fragment_time;
out vec3 fragment_position;

// Shader functionalty
void main()
{
    // Rotation matrix, from current_time
    // Top left 2x2 is the rotation matrix
    mat4 rotation_matrix = mat4(
        cos(current_time), -sin(current_time), 0.0, 0.0,
        sin(current_time), cos(current_time), 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,  
        0.0, 0.0, 0.0, 1.0
    );

    // Apply the rotation matrix to the position
    vec4 rotated_position = rotation_matrix * vec4(position, 1.0);

    // Apply the model matrix to the rotated position
    gl_Position = model_matrix * rotated_position;

    // Pass the color and time to the fragment shader
    fragment_color = color;
    fragment_time = current_time;
}