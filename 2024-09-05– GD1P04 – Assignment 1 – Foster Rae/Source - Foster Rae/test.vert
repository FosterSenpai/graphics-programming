#version 460 core

// How to read the vertex data.
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

// Outputs to fragment shader.
out vec2 TexCoord;
out vec3 FragPos;
out vec3 Normal;

// Inputs from application.
uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    // Apply the transformations to the vertex position.
    gl_Position = projection * view * transform * vec4(aPos, 1.0);
    // Pass the texture coordinates to the fragment shader.
    TexCoord = aTexCoord;
    // Pass the fragment position and normal to the fragment shader.
    FragPos = vec3(transform * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(transform))) * aNormal;
}