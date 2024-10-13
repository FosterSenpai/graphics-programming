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