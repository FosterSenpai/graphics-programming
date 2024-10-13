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
	 *	      Remember to free the image data after use with stbi_image_free(). \n
	 *		  Remember stbi_set_flip_vertically_on_load() before loading the image if needed.
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
	/**
	 * @brief Sets the texture coordinates for a single row spritesheet.
	 *
	 * @param vertices The vertices of the object to set the texture coordinates for.
	 * @param col The column of the spritesheet to set.
	 * @param total_cols The total number of columns in the spritesheet.
	 */
	static void set_single_row_spritesheet_coords(GLfloat* vertices, int col, int total_cols);
};
