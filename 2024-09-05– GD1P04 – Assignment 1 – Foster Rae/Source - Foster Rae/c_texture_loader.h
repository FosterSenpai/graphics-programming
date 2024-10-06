// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_texture_loader.h
// Description : Handles the loading of textures.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/
#pragma once
#include <glew.h>

/**
 * @class c_texture_loader
 * @brief Handles the loading of textures.
 */
class c_texture_loader
{
public:

	// == Public Methods ==
	/**
	 * @brief Loads an image from the file path provided.
	 *  @note The image is loaded using stb_image.h. \n
	 *	      Remember to free the image data after use with stbi_image_free().
	 *
	 *	@param file_path The file path to the image.
	 *	@param width Variable to store the width of the image.
	 *	@param height Variable to store the height of the image.
	 *	@param components Variable to store the number of components in the image.
	 */
	static unsigned char* load_image(const char* file_path, int* width, int* height, int* components);
	/**
	 * @brief Creates a texture from the image data provided.
	 *
	 * @param image_data Variable to store the image data.
	 * @param width Variable to store the width of the image.
	 * @param height Variable to store the height of the image.
	 * @param components Variable to store the number of components in the image.
	 * @return The texture ID.
	 */
	static GLuint create_texture(const unsigned char* image_data, const int width, const int height, const int components);
};
