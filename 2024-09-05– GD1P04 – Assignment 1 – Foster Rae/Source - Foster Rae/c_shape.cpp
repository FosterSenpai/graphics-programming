#include "c_shape.h"
#include <stb_image.h>
#include "c_texture_loader.h"

void c_shape::add_texture(const char* texture_path)
{
	// Load the image data.
	int width, height, components;
	unsigned char* image_data = c_texture_loader::load_image(texture_path, &width, &height, &components);
	// Create the texture.
	GLuint texture = c_texture_loader::create_texture(image_data, width, height, components);
	// Add to the textures vector.
	textures_.push_back(texture);
	// Free the image data.
	stbi_image_free(image_data);
}

c_shape::~c_shape()
{
	// Delete the buffers.
	glDeleteVertexArrays(1, &vao_);
	glDeleteBuffers(1, &vbo_);
	glDeleteBuffers(1, &ebo_);
}

void c_shape::update_model_matrix()
{
	// Update the model matrix.
	model_matrix = glm::mat4(1.0f);
    model_matrix = glm::translate(model_matrix, position);
    model_matrix = glm::rotate(model_matrix, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
    model_matrix = glm::scale(model_matrix, scale);
}
