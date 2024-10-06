/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name :cShaderLoader.h
Description : Class with static methods to load and compile shaders.
Author : Foster Rae
Mail : Foster.Rae@mds.ac.nz
************************************************************************/
#pragma once
#include <iostream>
#include "Dependencies/GLEW/glew.h"
#include "Dependencies/GLFW/glfw3.h"

/**
 * @class c_shader_loader
 * @brief Handles the loading and compiling of shaders.
 */
class c_shader_loader
{
public:

	// == Public Methods ==
	/**
	 * @brief Loads and compiles the shaders from the file paths provided.

	 * @param vertex_shader_filename The file path to the vertex shader.
	 * @param fragment_shader_filename The file path to the fragment shader.
	 * @return A GLuint to the created shader program.
	 */
	static GLuint create_program(const char* vertex_shader_filename, const char* fragment_shader_filename);

private:

	// == Constructors / Destructors ==
	c_shader_loader(void);
	~c_shader_loader(void);

	// == Private Methods ==
	/**
	 * @brief Creates a shader object from the shader type and file path provided.
	 *
	 * @param shader_type The type of shader to create.
	 * @param shader_name The file path to the shader. 
	 * @return The shader ID.
	 */
	static GLuint create_shader(GLenum shader_type, const char* shader_name);
	/**
	 * @brief Reads the shader file and returns the shader code as a string.
	 *
	 * @param filename The file path to the shader.
	 * @return The shader code as a string.
	 */
	static std::string read_shader_file(const char* filename);
	/**
	 * @brief Prints the error details for the shader or program.
	 *
	 * @param is_shader Whether the error is for a shader or program.
	 * @param id The ID of the shader or program.
	 * @param name The name of the shader or program.
	 */
	static void print_error_details(bool is_shader, GLuint id, const char* name);
};
