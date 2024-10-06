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
	 */
	void static initialize_glfw();
	/**
	 * @brief Initializes GLEW.
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
	 * @brief Initializes the quads.
	 * @note Creates two quads at the bottom left and bottom right of the screen,
	 *	     with textures applied to them.
	 *		 \n Create the needed objects globally and pass them in.
	 *
	 * @param quad_vao The vertex array object for the quad.
	 * @param quad_vbo The vertex buffer object for the quad.
	 * @param quad_ebo The element buffer object for the quad.
	 * @param texture_id The texture ID for the quad.
	 * @return A GLuint to the created shader program.
	 */
	GLuint static initialize_quads(GLuint &quad_vao, GLuint &quad_vbo, GLuint &quad_ebo, GLuint &texture_id);
	/**
	 * @brief Initializes the hexagons.
	 * @note Creates two spinning multi-coloured hexagons.
	 *		 \n Create the needed objects globally and pass them in.
	 *
	 * @param hex_vao The vertex array object for the hexagon.
	 * @param hex_vbo The vertex buffer object for the hexagon.
	 * @param hex_ebo The element buffer object for the hexagon.
	 * @return A GLuint to the created shader program.
	 */
	GLuint static initialize_hexagons(GLuint &hex_vao , GLuint &hex_vbo, GLuint &hex_ebo);
};
