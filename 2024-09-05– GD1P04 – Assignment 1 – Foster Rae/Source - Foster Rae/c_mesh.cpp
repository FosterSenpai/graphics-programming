#include "c_mesh.h"

c_mesh::c_mesh(const std::vector<s_vertex>& vertices, const std::vector<GLuint>& indices, const std::vector<s_texture>& textures)
    : vertices(vertices), indices(indices), textures(textures) {
    // Set up the mesh data.
    setup_mesh();
}

void c_mesh::draw(GLuint program_id)
{
    // Set the texture count.
    GLuint diffuse_count = 1;
    GLuint specular_count = 1;

    // Bind the textures.
    for (GLuint i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // Activate the texture unit first before binding.
        std::string number;
        std::string name = textures[i].type;
        if (name == "texture_diffuse")
        {
            number = std::to_string(diffuse_count++);
        }
        else if (name == "texture_specular")
        {
            number = std::to_string(specular_count++);
        }
        // Set the sampler to the correct texture unit.
        glUniform1i(glGetUniformLocation(program_id, (name + number).c_str()), i); // Concat to get the uniform name.
        glBindTexture(GL_TEXTURE_2D, textures[i].id);
    }

    // Draw the mesh.
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // Reset the active texture.
    glActiveTexture(GL_TEXTURE0);
}

void c_mesh::setup_mesh()
{
    // Generate the buffers.
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);

    // Bind the VAO.
    glBindVertexArray(vao);

    // Bind the VBO and EBO.
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(s_vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);

    // Set the vertex attribute pointers.
    // Vertex Positions.
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(s_vertex), static_cast<void*>(0));
    // Vertex Normals.
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(s_vertex), reinterpret_cast<void*>(offsetof(s_vertex, normal)));
    // Vertex Texture Coords.
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(s_vertex), reinterpret_cast<void*>(offsetof(s_vertex, tex_coords)));

    // Unbind the VAO.
    glBindVertexArray(0);
}
