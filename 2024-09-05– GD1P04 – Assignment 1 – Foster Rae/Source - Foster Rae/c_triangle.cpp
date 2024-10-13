#include "c_triangle.h"

void c_triangle::init()
{
    // Initialize triangle data.
	vertices_ = {
	    // Positions        // Colors         // Texture Coords
	    0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  0.5f, 1.0f, // Top
	   -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  0.0f, 0.0f, // Bottom-left
	    0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f,  1.0f, 0.0f  // Bottom-right
	};

	indices_ = { 0, 1, 2 };

	// Generate and bind VAO, VBO, and EBO.
	glGenVertexArrays(1, &vao_);
	glBindVertexArray(vao_);

	glGenBuffers(1, &vbo_);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_);
	glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(GLfloat), vertices_.data(), GL_STATIC_DRAW);

	glGenBuffers(1, &ebo_);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(GLuint), indices_.data(), GL_STATIC_DRAW);

	// Set the vertex attribute pointers.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), static_cast<GLvoid*>(nullptr));
	glEnableVertexAttribArray(0); // Position.

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1); // Color.

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), reinterpret_cast<GLvoid*>(6 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2); // Texture coords.

	glBindVertexArray(0); // Unbind ready for next VAO.
}

void c_triangle::draw(GLuint shader_program)
{
    // Bind the VAO.
    glBindVertexArray(vao_);
	// Send the model matrix to the shader.
    glUniformMatrix4fv(glGetUniformLocation(shader_program, "model_matrix"), 1, GL_FALSE, glm::value_ptr(model_matrix));

    // Bind each texture and draw the triangle.
    // Will draw each texture on top of each other starting from the first texture added.
    for (const auto& texture : textures_) {
        glBindTexture(GL_TEXTURE_2D, texture);
        glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, nullptr);
    }

    // Unbind the VAO.
    glBindVertexArray(0);
}
