#include "c_texture_loader.h"
#include <iostream>
#include <stb_image.h>

// == Public Methods ==
unsigned char* c_texture_loader::load_image(const char* file_path, int* width, int* height, int* components)
{
	// Flip the image vertically.
	stbi_set_flip_vertically_on_load(true);
	// Load the image and return the data.
	unsigned char* image_data = stbi_load(file_path, width, height, components, 0);
	// Check if the image data is valid.
	if (image_data == nullptr)
		{
		std::cout << "Failed to load image: " << file_path << '\n';
		}
    return image_data;
}
GLuint c_texture_loader::create_texture(const unsigned char* image_data, const int width, const int height, const int components)
{
    GLuint texture; // Create a texture object.
    glGenTextures(1, &texture); // Generate a texture object.
    glBindTexture(GL_TEXTURE_2D, texture); // Bind the texture object to the target slot.
	 
    // Set the filtering and mipmap parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Check how many components the loaded image has
    GLint loaded_components = (components == 4) ? GL_RGBA : GL_RGB;

    // Generate the texture & mipmap
    glTexImage2D(GL_TEXTURE_2D, 0, loaded_components, width, height, 0, loaded_components, GL_UNSIGNED_BYTE, image_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    // Unbind the texture
    glBindTexture(GL_TEXTURE_2D, 0);

    return texture; // Pass the generated texture back to the caller.
}
