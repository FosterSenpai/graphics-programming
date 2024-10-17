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

#include "Dependencies/GLM/glm.hpp"
#include "Dependencies/GLEW/glew.h"
#include "Dependencies/GLFW/glfw3.h"

/**
 * @class c_shader_loader
 * @brief Handles the loading and compiling of shaders.
 */
class c_shader_loader
{
public:
	// == Public Members ==
	GLuint program_id; // The ID of the shader program.

	// == Public Methods ==
	/**
	 * @brief Loads and compiles the shaders from the file paths provided.

	 * @param vertex_shader_filename The file path to the vertex shader.
	 * @param fragment_shader_filename The file path to the fragment shader.
	 * @return A GLuint to the created shader program.
	 */
	static GLuint create_program(const char* vertex_shader_filename, const char* fragment_shader_filename);

	// == Uniform Setters ==
	// Fairly self-explanatory, these functions set the uniform values in the shader.
	// They take the program ID, the name of the uniform, and the value to set.
	// The vector functions can either take a glm::vec or individual floats.

	static void set_bool(GLuint program, const std::string& name, bool value);
	static void set_int(GLuint program, const std::string& name, int value);
	static void set_float(GLuint program, const std::string& name, float value);
	static void setVec2(GLuint program, const std::string &name, const glm::vec2 &value);
	static void set_vec2(GLuint program, const std::string& name, float x, float y);
	static void setVec3(GLuint program, const std::string &name, const glm::vec3 &value);
	static void set_vec3(GLuint program, const std::string& name, float x, float y, float z);
	static void setVec4(GLuint program, const std::string &name, const glm::vec4 &value);
	static void set_vec4(GLuint program, const std::string& name, float x, float y, float z, float w);
	static void setMat2(GLuint program, const std::string &name, const glm::mat2 &mat);
	static void setMat3(GLuint program, const std::string &name, const glm::mat3 &mat);
	static void setMat4(GLuint program, const std::string &name, const glm::mat4 &mat);


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
