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
	/**
	 * @brief Initializes the quad.
	 *
	 * @param quad_vao Global variable for the vertex array object of the quad.
	 * @param quad_vbo Global variable for the vertex buffer object of the quad.
	 * @param quad_ebo Global variable for the element buffer object of the quad.
	 * @param texture_id1 Global variable for the first texture ID.
	 * @param texture_id2 Global variable for the second texture ID.
	 *  @param texture_id3 Global variable for the third texture ID. ( Sprite Sheet )
	 * @return The Program ID. (GLuint)
	 */
	static GLuint initialize_quads(GLuint &quad_vao, GLuint &quad_vbo, GLuint &quad_ebo, GLuint &texture_id1, GLuint &texture_id2, GLuint& texture_id3);
};
