/***********************************************************************
Bachelor of Software Engineering
Media Design School
Auckland
New Zealand
(c) 2024 Media Design School
File Name :cShaderLoader.h
Description : Class to load and compile shaders.
Author : Foster Rae
Mail : Foster.Rae@mds.ac.nz
************************************************************************/
/* Todo: Add function descriptions
************************************************************************/
#pragma once

// Library Includes
#include <iostream>

#include "Dependencies/GLEW/glew.h" // GLEW must be included before GLFW.
#include "Dependencies/GLFW/glfw3.h"

class c_shader_loader
{
public:
	static GLuint create_program(const char* vertex_shader_filename, const char* fragment_shader_filename);

private:
	c_shader_loader(void);
	~c_shader_loader(void);
	static GLuint create_shader(GLenum shader_type, const char* shader_name);
	static std::string read_shader_file(const char* filename);
	static void print_error_details(bool is_shader, GLuint id, const char* name);
};
