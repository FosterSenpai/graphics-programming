// /***********************************************************************
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
// (c) 2024 Media Design School
// File Name : c_graphics_utils.h
// Description : Utility functions for the pipeline.
// Author : Foster Rae
// Mail : Foster.Rae@mds.ac.nz
// ************************************************************************/
#pragma once
#include <glew.h>
#include "c_shader_loader.h"

/**
 * @class c_graphics_utils
 * @brief Handles general graphics utility functions.
 */
class c_graphics_utils
{
public:

	// == Public Methods ==
	/**
	 * @brief Initializes GLFW.
	 * @note Call this before initializing GLEW.
	 */
	void static initialize_glfw();
	/**
	 * @brief Initializes GLEW.
	 *
	 * @return 0 if initialization is successful, -1 if it fails.
	 */
	int static initialize_glew();
	/**
	 * @brief Creates a window with the given parameters.
	 *
	 * @param width The width of the window.
	 * @param height The height of the window.
	 * @param title The title of the window.
	 * @return A pointer to the created window.
	 */
	static GLFWwindow* create_window(int width, int height, const char* title);

	// == Image Loading ==
	/**
	 * @brief Loads an image from the file path provided.
	 *
	 * @param file_path The file path to the image.
	 * @return The ID of the loaded image.
	 */
	static GLuint load_image(const char* file_path);
};
